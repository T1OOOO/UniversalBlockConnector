#include "tcpclientcontroller.h"
#include <QtDebug>

namespace {
constexpr quint16 defaultClientPort = 5001;
constexpr int reconnectTimeout = 1000;
} // namespace

TcpClientController::TcpClientController(QObject *parent)
    : ByteArrayDataController{parent}, m_clientPort{defaultClientPort},
      m_reconnect{false} {
  m_sock = new QTcpSocket(this);
  connect(m_sock, &QTcpSocket::readyRead, this,
          &TcpClientController::slot_onReadyRead);
  connect(m_sock, &QTcpSocket::stateChanged, this,
          &TcpClientController::slot_onStateChanged);
  connect(m_sock, &QTcpSocket::errorOccurred, this,
          &TcpClientController::slot_onErrorOccurred);

  m_widget = new TcpClientWidget();
  connect(m_widget, &TcpClientWidget::signal_connect, this,
          &TcpClientController::slot_onConnect);
  connect(m_widget, &TcpClientWidget::signal_reconnect, this,
          &TcpClientController::slot_onReconnect);
  connect(m_widget, &TcpClientWidget::signal_close, this,
          &TcpClientController::slot_onClose);

  connect(this, &TcpClientController::signal_open, m_widget,
          &TcpClientWidget::slot_onOpen);
  connect(this, &TcpClientController::signal_close, m_widget,
          &TcpClientWidget::slot_onClose);
  connect(this, &TcpClientController::signal_error, m_widget,
          &TcpClientWidget::slot_onError);
  registerWidget(m_widget);

  connect(&m_reconnectTimer, &QTimer::timeout, this,
          &TcpClientController::slot_onReconnectTimer);
}

bool TcpClientController::connectToHost(const QString &clientAddress,
                                        const quint16 clientPort) {
  m_clientAddress = clientAddress;
  m_clientPort = clientPort;

  close();
  m_sock->connectToHost(QHostAddress(clientAddress), clientPort);

  return true;
}

void TcpClientController::close() {
  m_sock->disconnectFromHost();
  m_sock->close();
}

void TcpClientController::write(const QByteArray &data) { m_sock->write(data); }

void TcpClientController::onReceiveData(QtNodes::PortType portType,
                                        QtNodes::PortIndex portIndex,
                                        const QByteArray &data) {
  write(data);
}

void TcpClientController::slot_onStateChanged(
    QAbstractSocket::SocketState state) {
  if (state == QAbstractSocket::SocketState::ConnectedState) {
    emit signal_open();
    m_widget->setTitle("Connected");
  } else if (state == QAbstractSocket::SocketState::ConnectingState) {
    emit signal_connecting();
    m_widget->setTitle("Connecting");
  } else if (state == QAbstractSocket::SocketState::ClosingState) {
  } else if (state == QAbstractSocket::SocketState::UnconnectedState) {
    emit signal_close();
    m_widget->setTitle("Disconnected");

    if (m_reconnect) {
      if (!m_reconnectTimer.isActive()) {
        m_reconnectTimer.start(reconnectTimeout);
      }
    } else {
      close();
    }
  }
}

void TcpClientController::slot_onErrorOccurred(
    QAbstractSocket::SocketError error) {}

void TcpClientController::slot_onReadyRead() {
  if (m_sock->bytesAvailable() == 0) {
    return;
  }

  QByteArray data = m_sock->readAll();

  sendDataAll(data);
}

void TcpClientController::slot_onReconnectTimer() {
  if (m_sock->state() == QAbstractSocket::SocketState::ConnectedState ||
      m_sock->state() == QAbstractSocket::SocketState::ConnectingState) {
    return;
  }

  m_sock->connectToHost(QHostAddress(m_clientAddress), m_clientPort);
}

void TcpClientController::slot_onConnect(const QString &clientAddress,
                                         const quint16 clientPort) {
  if (!connectToHost(clientAddress, clientPort)) {
    logger()->debug() << "Failed to open port";
  }
}

void TcpClientController::slot_onReconnect(const bool reconnect) {
  m_reconnect = reconnect;
}

void TcpClientController::slot_onClose() { close(); }
