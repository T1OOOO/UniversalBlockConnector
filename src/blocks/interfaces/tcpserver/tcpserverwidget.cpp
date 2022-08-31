#include "tcpserverwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QNetworkInterface>

namespace {
const QString defaultSrcAddress = "127.0.0.1";
constexpr quint16 defaultSrcPort = 5000;
const QString defaultClientAddress = "127.0.0.1";
constexpr quint16 defaultClientPort = 5001;
} // namespace

TcpServerWidget::TcpServerWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  auto *srcBox = new QGroupBox("Source", widget);
  layout->addWidget(srcBox, 0, 0);

  auto *srcBoxLayout = new QGridLayout(srcBox);

  auto *srcAddressLabel = new QLabel("Address:", srcBox);
  srcBoxLayout->addWidget(srcAddressLabel, 0, 0);
  m_srcAddress = new QComboBox(srcBox);
  for (const auto &address : QNetworkInterface::allAddresses()) {
    m_srcAddress->addItem(address.toString());
  }
  srcBoxLayout->addWidget(m_srcAddress, 0, 1);

  auto srcPortLabel = new QLabel("Port:", srcBox);
  srcBoxLayout->addWidget(srcPortLabel, 1, 0);
  m_srcPort = new QSpinBox(srcBox);
  m_srcPort->setRange(1, std::numeric_limits<quint16>::max());
  m_srcPort->setValue(defaultSrcPort);
  srcBoxLayout->addWidget(m_srcPort, 1, 1);

  m_open = new QPushButton("Open", widget);
  m_open->setCheckable(true);
  connect(m_open, &QPushButton::clicked, this, &TcpServerWidget::slot_onPush);
  layout->addWidget(m_open, 1, 0);
}

QJsonObject TcpServerWidget::saveSettings() const {
  QJsonObject obj;
  obj["srcAddress"] = m_srcAddress->currentText();
  obj["srcPort"] = m_srcPort->value();

  return obj;
}

void TcpServerWidget::restoreSettings(const QJsonObject &obj) {
  m_srcAddress->setCurrentText(obj["srcAddress"].toString());
  m_srcPort->setValue(obj["srcPort"].toInt());
}

void TcpServerWidget::slot_onPush() {
  if (!m_open->isChecked()) {
    emit signal_close();
  } else {
    const QString srcAddress = m_srcAddress->currentText();
    const quint16 srcPort = m_srcPort->value();
    emit signal_open(srcAddress, srcPort);
  }
}

void TcpServerWidget::slot_onOpen() {
  m_open->setText("Close");
  m_open->setChecked(true);
}
void TcpServerWidget::slot_onClose() {
  m_open->setText("Open");
  m_open->setChecked(false);
}

void TcpServerWidget::slot_onError(const QString &str) {
  m_open->setText("Open");
  m_open->setChecked(false);
}
