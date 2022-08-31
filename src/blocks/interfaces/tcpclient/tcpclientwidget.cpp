#include "tcpclientwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QNetworkInterface>

namespace {
const QString defaultSrcAddress = "127.0.0.1";
constexpr quint16 defaultSrcPort = 10000;
const QString defaultClientAddress = "127.0.0.1";
constexpr quint16 defaultClientPort = 5000;
} // namespace

TcpClientWidget::TcpClientWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  //  auto *srcBox = new QGroupBox("Source", widget);
  //  layout->addWidget(srcBox, 0, 0);

  //  auto *srcBoxLayout = new QGridLayout(srcBox);

  //  auto *srcAddressLabel = new QLabel("Address:", srcBox);
  //  srcBoxLayout->addWidget(srcAddressLabel, 0, 0);
  //  m_srcAddress = new QComboBox(srcBox);
  //  for (const auto &address : QNetworkInterface::allAddresses()) {
  //    m_srcAddress->addItem(address.toString());
  //  }
  //  srcBoxLayout->addWidget(m_srcAddress, 0, 1);

  //  auto *srcPortLabel = new QLabel("Port:", srcBox);
  //  srcBoxLayout->addWidget(srcPortLabel, 1, 0);
  //  m_srcPort = new QSpinBox(srcBox);
  //  m_srcPort->setRange(1, std::numeric_limits<quint16>::max());
  //  m_srcPort->setValue(defaultSrcPort);
  //  srcBoxLayout->addWidget(m_srcPort, 1, 1);

  auto *clientBox = new QGroupBox("Client", widget);
  layout->addWidget(clientBox, 1, 0);

  auto *clientLayout = new QGridLayout(clientBox);

  auto *clientAddressLabel = new QLabel("Address:", clientBox);
  clientLayout->addWidget(clientAddressLabel, 0, 0);
  m_clientAddress = new QComboBox(clientBox);
  m_clientAddress->setEditable(true);
  for (const auto &address : QNetworkInterface::allAddresses()) {
    m_clientAddress->addItem(address.toString());
  }
  clientLayout->addWidget(m_clientAddress, 0, 1);

  auto *clientPortLabel = new QLabel("Port:", clientBox);
  clientLayout->addWidget(clientPortLabel, 1, 0);
  m_clientPort = new QSpinBox(clientBox);
  m_clientPort->setRange(1, std::numeric_limits<quint16>::max());
  m_clientPort->setValue(defaultClientPort);
  clientLayout->addWidget(m_clientPort, 1, 1);

  m_reconnect = new QCheckBox("Reconnect", clientBox);
  clientLayout->addWidget(m_reconnect, 2, 0, 1, 2);

  m_open = new QPushButton("Open", widget);
  m_open->setCheckable(true);
  connect(m_open, &QPushButton::clicked, this, &TcpClientWidget::slot_onPush);
  layout->addWidget(m_open, 2, 0);
}

QJsonObject TcpClientWidget::saveSettings() const {
  QJsonObject obj;
  //  obj["srcAddress"] = m_srcAddress->currentText();
  //  obj["srcPort"] = m_srcPort->value();
  obj["clientAddress"] = m_clientAddress->currentText();
  obj["clientPort"] = m_clientPort->value();

  return obj;
}

void TcpClientWidget::restoreSettings(const QJsonObject &obj) {
  //  m_srcAddress->setCurrentText(obj["srcAddress"].toString());
  //  m_srcPort->setValue(obj["srcPort"].toInt());
  m_clientAddress->setCurrentText(obj["clientAddress"].toString());
  m_clientPort->setValue(obj["clientPort"].toInt());
}

void TcpClientWidget::slot_onPush() {
  if (!m_open->isChecked()) {
    emit signal_close();
  } else {
    //    const QString srcAddress = m_srcAddress->currentText();
    //    const quint16 srcPort = m_srcPort->value();

    const QString clientAddress = m_clientAddress->currentText();
    const quint16 clientPort = m_clientPort->value();

    const bool reconnect = m_reconnect->isChecked();

    emit signal_reconnect(reconnect);
    emit signal_connect(clientAddress, clientPort);
  }
}

void TcpClientWidget::slot_onOpen() {
  m_open->setText("Close");
  m_open->setChecked(true);
}

void TcpClientWidget::slot_onClose() {
  m_open->setText("Open");
  m_open->setChecked(false);
}

void TcpClientWidget::slot_onError(const QString &str) {
  m_open->setText("Open");
  m_open->setChecked(false);
}
