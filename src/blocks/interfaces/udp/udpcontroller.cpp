#include "udpcontroller.h"
#include <QNetworkDatagram>
#include <QtDebug>

namespace {
constexpr quint16 defaultClientPort = 5001;
}

UdpController::UdpController(QObject *parent)
    : ByteArrayDataController{parent}, m_clientPort{defaultClientPort} {
  m_sock = new QUdpSocket(this);
  connect(m_sock, &QUdpSocket::readyRead, this,
          &UdpController::slot_onReadyRead);
  connect(m_sock, &QUdpSocket::stateChanged, this,
          &UdpController::slot_onStateChanged);
  connect(m_sock, &QUdpSocket::errorOccurred, this,
          &UdpController::slot_onErrorOccurred);

  m_widget = new UdpWidget();
  connect(m_widget, &UdpWidget::signal_open, this, &UdpController::slot_onOpen);
  connect(m_widget, &UdpWidget::signal_clientParams, this,
          &UdpController::slot_onClientParams);
  connect(m_widget, &UdpWidget::signal_close, this,
          &UdpController::slot_onClose);

  connect(this, &UdpController::signal_open, m_widget, &UdpWidget::slot_onOpen);
  connect(this, &UdpController::signal_close, m_widget,
          &UdpWidget::slot_onClose);
  connect(this, &UdpController::signal_error, m_widget,
          &UdpWidget::slot_onError);
  registerWidget(m_widget);
}

UdpController::~UdpController() { close(); }

bool UdpController::open(const QString &address, const qint16 port) {
  close();

  if (!m_sock->bind(QHostAddress(address), port)) {
    emit signal_error("Udp does not open");

    return false;
  }

  return true;
}
void UdpController::close() { m_sock->close(); }

void UdpController::write(const QByteArray &data) {
  m_sock->writeDatagram(data, QHostAddress(m_clientAddress), m_clientPort);
}

void UdpController::slot_onStateChanged(QAbstractSocket::SocketState state) {
  if (state == QAbstractSocket::SocketState::BoundState) {
    emit signal_open();
  } else if (state == QAbstractSocket::SocketState::UnconnectedState) {
    emit signal_close();

    close();
  }
}

void UdpController::slot_onErrorOccurred(QAbstractSocket::SocketError error) {
  emit signal_error("Error: " + m_sock->errorString());
}

void UdpController::slot_onReadyRead() {
  while (m_sock->hasPendingDatagrams()) {
    QNetworkDatagram datagram = m_sock->receiveDatagram();

    sendDataAll(datagram.data());
  }
}

void UdpController::onReceiveData(PortType portType, PortIndex portIndex,
                                  const QByteArray &data) {
  write(data);
}

void UdpController::slot_onOpen(const QString &address, const quint16 port) {
  if (!open(address, port)) {
    qDebug() << "Failed to open port";
  }
}

void UdpController::slot_onClientParams(const QString &address,
                                        const quint16 port) {
  m_clientAddress = address;
  m_clientPort = port;
}

void UdpController::slot_onClose() { close(); }
