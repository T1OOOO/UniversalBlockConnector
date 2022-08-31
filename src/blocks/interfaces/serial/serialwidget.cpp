#include "serialwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QtSerialPort/QSerialPortInfo>

namespace {
const QString defaultSrcAddress = "127.0.0.1";
constexpr quint16 defaultSrcPort = 5000;
const QString defaultClientAddress = "127.0.0.1";
constexpr quint16 defaultClientPort = 5001;
} // namespace

SerialWidget::SerialWidget(QWidget *parent) : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  auto *portLabel = new QLabel("Port: ", widget);
  layout->addWidget(portLabel, 0, 0);
  m_port = new QComboBox(widget);
  m_port->setEditable(true);
  for (const auto &info : QSerialPortInfo::availablePorts()) {
    m_port->addItem(info.portName());
  }
  layout->addWidget(m_port, 0, 1);

  auto *baudRateLabel = new QLabel("BaudRate: ", widget);
  layout->addWidget(baudRateLabel, 1, 0);
  m_baudRate = new QComboBox(widget);
  m_baudRate->setEditable(true);
  for (const auto &baudRate : QSerialPortInfo::standardBaudRates().mid(12, 5)) {
    m_baudRate->addItem(QString::number(baudRate), baudRate);
  }
  layout->addWidget(m_baudRate, 1, 1);

  auto *dataBitsLabel = new QLabel("DataBits: ", widget);
  layout->addWidget(dataBitsLabel, 2, 0);
  m_dataBits = new QComboBox(widget);
  static const QList<QSerialPort::DataBits> dataBitsList = {
      QSerialPort::Data5, QSerialPort::Data6, QSerialPort::Data7,
      QSerialPort::Data8};
  for (const auto &dataBits : dataBitsList) {
    m_dataBits->addItem(QString::number(dataBits), dataBits);
  }
  m_dataBits->setCurrentIndex(3);
  layout->addWidget(m_dataBits, 2, 1);

  auto *parityLabel = new QLabel("Parity: ", widget);
  layout->addWidget(parityLabel, 3, 0);
  m_parity = new QComboBox(widget);
  static const QStringList parityListNames = {"No", "Even", "Odd", "Space",
                                              "Mark"};
  static const QList<QSerialPort::Parity> parityList = {
      QSerialPort::NoParity, QSerialPort::EvenParity, QSerialPort::OddParity,
      QSerialPort::SpaceParity, QSerialPort::MarkParity};
  for (int i = 0; i < parityList.size(); i++) {
    const auto &parityName = parityListNames.at(i);
    const auto parity = parityList.at(i);

    m_parity->addItem(parityName, parity);
  }
  m_parity->setCurrentIndex(0);
  layout->addWidget(m_parity, 3, 1);

  auto *stopBitsLabel = new QLabel("StopBits: ", widget);
  layout->addWidget(stopBitsLabel, 4, 0);
  m_stopBits = new QComboBox(widget);
  static const QList<QSerialPort::StopBits> stopBitsList = {};
  for (const auto &stopBits : dataBitsList) {
    m_stopBits->addItem(QString::number(stopBits), stopBits);
  }
  m_stopBits->setCurrentIndex(0);
  layout->addWidget(m_stopBits, 4, 1);

  auto *flowControlLabel = new QLabel("FlowControl: ", widget);
  layout->addWidget(flowControlLabel, 5, 0);
  m_flowControl = new QComboBox(widget);
  static const QStringList flowControlListNames = {"No", "Hw", "Sw"};
  static const QList<QSerialPort::FlowControl> flowControlList = {
      QSerialPort::NoFlowControl, QSerialPort::HardwareControl,
      QSerialPort::SoftwareControl};
  for (int i = 0; i < flowControlList.size(); i++) {
    const auto &flowControlName = flowControlListNames.at(i);
    const auto flowControl = flowControlList.at(i);

    m_flowControl->addItem(flowControlName, flowControl);
  }
  m_flowControl->setCurrentIndex(0);
  layout->addWidget(m_flowControl, 5, 1);

  m_open = new QPushButton("Open", widget);
  m_open->setCheckable(true);
  connect(m_open, &QPushButton::clicked, this, &SerialWidget::slot_onPush);
  layout->addWidget(m_open, 6, 0, 1, 2);
}

QJsonObject SerialWidget::saveSettings() const {
  QJsonObject obj;
  obj["port"] = m_port->currentText();
  obj["baudRate"] = m_baudRate->currentData().value<qint32>();
  obj["dataBits"] = m_dataBits->currentData().value<QSerialPort::DataBits>();
  obj["parity"] = m_parity->currentData().value<QSerialPort::Parity>();
  obj["stopBits"] = m_stopBits->currentData().value<QSerialPort::StopBits>();
  obj["flowControl"] =
      m_flowControl->currentData().value<QSerialPort::FlowControl>();

  return obj;
}

void SerialWidget::restoreSettings(const QJsonObject &obj) {
  m_port->setCurrentText(obj["port"].toString());

  const int baudRateIdx = m_baudRate->findData(obj["baudRate"].toInt());
  if (baudRateIdx > 0) {
    m_baudRate->setCurrentIndex(baudRateIdx);
  }

  const int dataBitsIdx = m_dataBits->findData(obj["dataBits"].toInt());
  if (dataBitsIdx > 0) {
    m_dataBits->setCurrentIndex(dataBitsIdx);
  }

  const int parityIdx = m_parity->findData(obj["parity"].toInt());
  if (parityIdx > 0) {
    m_parity->setCurrentIndex(parityIdx);
  }

  const int stopBitsIdx = m_stopBits->findData(obj["stopBits"].toInt());
  if (stopBitsIdx > 0) {
    m_stopBits->setCurrentIndex(stopBitsIdx);
  }

  const int flowControlIdx =
      m_flowControl->findData(obj["flowControl"].toInt());
  if (flowControlIdx > 0) {
    m_flowControl->setCurrentIndex(flowControlIdx);
  }
}

void SerialWidget::slot_onPush() {
  if (!m_open->isChecked()) {
    emit signal_close();
  } else {
    SerialSettings settings;
    settings.port = m_port->currentText();
    settings.baudRate = m_baudRate->currentData().value<qint32>();
    settings.dataBits =
        m_dataBits->currentData().value<QSerialPort::DataBits>();
    settings.parity = m_parity->currentData().value<QSerialPort::Parity>();
    settings.stopBits =
        m_stopBits->currentData().value<QSerialPort::StopBits>();
    settings.flowControl =
        m_flowControl->currentData().value<QSerialPort::FlowControl>();

    emit signal_open(settings);
  }
}

void SerialWidget::slot_onOpen() { m_open->setText("Close"); }
void SerialWidget::slot_onClose() { m_open->setText("Open"); }

void SerialWidget::slot_onError(const QString &str) {
  m_open->setText("Open");
  m_open->setChecked(false);
}
