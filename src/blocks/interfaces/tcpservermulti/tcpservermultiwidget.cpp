#include "tcpservermultiwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QNetworkInterface>

namespace {
const QString defaultSrcAddress = "127.0.0.1";
constexpr quint16 defaultSrcPort = 5000;
const QString defaultClientAddress = "127.0.0.1";
constexpr quint16 defaultClientPort = 5001;
} // namespace

TcpServerMultiWidget::TcpServerMultiWidget(QWidget *parent)
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

  m_view = new QTableView(srcBox);
  m_view->horizontalHeader()->setStretchLastSection(true);
  m_view->setSelectionBehavior(QAbstractItemView::SelectRows);

  m_model = new SocketTableModel(m_view);
  m_view->setModel(m_model);

  m_delegate = new SocketTableDelegate(m_view);
  connect(m_delegate, &SocketTableDelegate::signal_close, this,
          &TcpServerMultiWidget::slot_onCloseSocket);
  m_view->setItemDelegateForColumn(1, m_delegate);
  srcBoxLayout->addWidget(m_view, 2, 0, 1, 2);

  m_view->resizeColumnsToContents();

  m_open = new QPushButton("Open", widget);
  m_open->setCheckable(true);
  connect(m_open, &QPushButton::clicked, this,
          &TcpServerMultiWidget::slot_onPush);
  layout->addWidget(m_open, 1, 0);
}

QJsonObject TcpServerMultiWidget::saveSettings() const {
  QJsonObject obj;
  obj["srcAddress"] = m_srcAddress->currentText();
  obj["srcPort"] = m_srcPort->value();

  return obj;
}

void TcpServerMultiWidget::restoreSettings(const QJsonObject &obj) {
  m_srcAddress->setCurrentText(obj["srcAddress"].toString());
  m_srcPort->setValue(obj["srcPort"].toInt());
}

SocketTableModel *TcpServerMultiWidget::getModel() const { return m_model; }

void TcpServerMultiWidget::updateColumnSize() {
  m_view->resizeColumnToContents(2);
}

void TcpServerMultiWidget::slot_onPush() {
  if (!m_open->isChecked()) {
    emit signal_close();
  } else {
    const QString srcAddress = m_srcAddress->currentText();
    const quint16 srcPort = m_srcPort->value();

    emit signal_open(srcAddress, srcPort);
  }
}

void TcpServerMultiWidget::slot_onOpen() {
  m_open->setText("Close");
  m_open->setChecked(true);
}
void TcpServerMultiWidget::slot_onClose() {
  m_open->setText("Open");
  m_open->setChecked(false);
}

void TcpServerMultiWidget::slot_onError(const QString &str) {
  m_open->setText("Open");
  m_open->setChecked(false);
}

void TcpServerMultiWidget::slot_onCloseSocket(const int num) {
  emit signal_closeSocket(num);
}
