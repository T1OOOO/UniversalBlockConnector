#include "serialcontroller.h"

namespace {
constexpr quint16 defaultClientPort = 5001;
}

SerialController::SerialController(QObject *parent)
    : ByteArrayDataController{parent}, m_clientPort{defaultClientPort} {
  m_sock = new QSerialPort(this);
  connect(m_sock, &QSerialPort::readyRead, this,
          &SerialController::slot_onReadyRead);

  m_widget = new SerialWidget();
  connect(m_widget, &SerialWidget::signal_open, this,
          &SerialController::slot_onOpen);
  connect(m_widget, &SerialWidget::signal_close, this,
          &SerialController::slot_onClose);

  connect(this, &SerialController::signal_open, m_widget,
          &SerialWidget::slot_onOpen);
  connect(this, &SerialController::signal_close, m_widget,
          &SerialWidget::slot_onClose);
  connect(this, &SerialController::signal_error, m_widget,
          &SerialWidget::slot_onError);
  registerWidget(m_widget);
}

SerialController::~SerialController() { close(); }

bool SerialController::open(const SerialSettings &settings) {
  close();

  m_sock->setBaudRate(settings.baudRate);
  m_sock->setDataBits(settings.dataBits);
  m_sock->setParity(settings.parity);
  m_sock->setStopBits(settings.stopBits);
  m_sock->setFlowControl(settings.flowControl);
  if (!m_sock->open(QSerialPort::ReadWrite)) {
    emit signal_error("Udp does not open");

    return false;
  }

  return true;
}
void SerialController::close() { m_sock->close(); }

void SerialController::write(const QByteArray &data) { m_sock->write(data); }

void SerialController::slot_onReadyRead() {
  while (m_sock->bytesAvailable() > 0) {
    QByteArray data = m_sock->readAll();

    sendDataAll(data);
  }
}

void SerialController::onReceiveData(PortType portType, PortIndex portIndex,
                                     const QByteArray &data) {
  write(data);
}

void SerialController::slot_onOpen(const SerialSettings &settings) {
  if (!open(settings)) {
    qDebug() << "Failed to open port";
  }
}

void SerialController::slot_onClose() { close(); }

void SerialController::slot_onErrorOccurred(
    QSerialPort::SerialPortError error) {
  emit signal_error("Error: " + m_sock->errorString());
}
