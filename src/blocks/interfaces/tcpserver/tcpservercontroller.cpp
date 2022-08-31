#include "tcpservercontroller.h"
#include <QtDebug>

TcpServerController::TcpServerController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_server = new QTcpServer(this);
  connect(m_server, &QTcpServer::newConnection, this,
          &TcpServerController::slot_onNewConnection);

  m_widget = new TcpServerWidget();
  connect(m_widget, &TcpServerWidget::signal_open, this,
          &TcpServerController::slot_onOpen);
  connect(m_widget, &TcpServerWidget::signal_close, this,
          &TcpServerController::slot_onClose);

  connect(this, &TcpServerController::signal_open, m_widget,
          &TcpServerWidget::slot_onOpen);
  connect(this, &TcpServerController::signal_close, m_widget,
          &TcpServerWidget::slot_onClose);
  connect(this, &TcpServerController::signal_error, m_widget,
          &TcpServerWidget::slot_onError);
  registerWidget(m_widget);
}

TcpServerController::~TcpServerController() { close(); }

bool TcpServerController::open(const QString &address, const qint16 port) {
  close();

  if (!m_server->listen(QHostAddress(address), port)) {
    emit signal_close();
    m_widget->setTitle("Closed");

    return false;
  }

  emit signal_open();
  m_widget->setTitle("Listen");

  return true;
}

void TcpServerController::close() {
  m_server->close();

  for (auto *sock : m_clientList) {
    sock->disconnect();
    sock->close();
    sock->deleteLater();
  }

  m_clientList.clear();

  emit signal_close();

  m_widget->setTitle("Closed");
}

void TcpServerController::write(const QByteArray &data) {
  for (auto *sock : m_clientList) {
    sock->write(data);
  }
}

void TcpServerController::slot_onNewConnection() {
  while (m_server->hasPendingConnections()) {
    QTcpSocket *socket = m_server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this,
            &TcpServerController::slot_onReadyRead);
    connect(socket, &QTcpSocket::stateChanged, this,
            &TcpServerController::slot_onStateChanged);
    connect(socket, &QTcpSocket::errorOccurred, this,
            &TcpServerController::slot_onErrorOccurred);

    m_clientList.push_back(socket);
  }
}

void TcpServerController::slot_onStateChanged(
    QAbstractSocket::SocketState state) {
  auto *sock = qobject_cast<QTcpSocket *>(sender());
  if (sock == nullptr) {
    return;
  }

  if (state == QAbstractSocket::SocketState::ListeningState) {
  } else if (state == QAbstractSocket::SocketState::UnconnectedState) {
    sock->disconnect(this);

    m_clientList.removeOne(sock);
    sock->deleteLater();
  }
}

void TcpServerController::slot_onErrorOccurred(
    QAbstractSocket::SocketError error) {
  auto *sock = qobject_cast<QTcpSocket *>(sender());
  if (sock == nullptr) {
    return;
  }

  sock->disconnect(sock);
  m_clientList.removeOne(sock);
  sock->deleteLater();

  m_server->close();
  m_widget->setTitle("Closed");
}

void TcpServerController::slot_onReadyRead() {
  auto *sock = qobject_cast<QTcpSocket *>(sender());
  if (sock == nullptr) {
    return;
  }

  if (sock->bytesAvailable() == 0) {
    return;
  }

  const QByteArray data = sock->readAll();

  emit signal_data(data);
}

void TcpServerController::onReceiveData(PortType portType, PortIndex portIndex,
                                        const QByteArray &data) {
  write(data);
}

void TcpServerController::slot_onOpen(const QString &address,
                                      const quint16 port) {
  if (!open(address, port)) {
  }
}

void TcpServerController::slot_onClose() { close(); }
