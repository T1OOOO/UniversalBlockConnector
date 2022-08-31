#include "bytearraydatawidget.h"

#include <QGroupBox>
#include <QPushButton>

namespace {
constexpr int defaultSize = 15;
}

ByteArrayDataWidget::ByteArrayDataWidget(QWidget *parent) : QWidget{parent} {
  m_layout = new QGridLayout(this);

  auto *ledBox = new QWidget(this);
  ledBox->setMinimumHeight(defaultSize);
  ledBox->setMaximumHeight(defaultSize);
  ledBox->setContentsMargins(0, 0, 0, 0);
  ledBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  auto *ledBoxLayout = new QGridLayout(ledBox);
  ledBoxLayout->setContentsMargins(0, 0, 0, 0);

  m_ledInTx = new LedWidget(ledBox);
  ledBoxLayout->addWidget(m_ledInTx, 0, 0);

  m_ledInRx = new LedWidget(ledBox);
  ledBoxLayout->addWidget(m_ledInRx, 0, 1);

  m_title = new QLabel(ledBox);
  m_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  ledBoxLayout->addWidget(m_title, 0, 2);

  m_ledOutRx = new LedWidget(ledBox);
  ledBoxLayout->addWidget(m_ledOutRx, 0, 3);

  m_ledOutTx = new LedWidget(ledBox);
  ledBoxLayout->addWidget(m_ledOutTx, 0, 4);

  m_layout->addWidget(ledBox, 0, 0);

  m_widget = new QWidget(this);
  m_layout->addWidget(m_widget, 1, 0);

  update();
}

void ByteArrayDataWidget::setTitle(const QString &str) {
  m_title->setText("<center>" + str + "</center>");
}

void ByteArrayDataWidget::slot_onReceiveData(const QByteArray &data) {
  onReceiveData(data);
}

void ByteArrayDataWidget::sendData(QtNodes::PortType type,
                                   QtNodes::PortIndex index,
                                   const QByteArray &data) {
  emit signal_sendData(type, index, data);
}

void ByteArrayDataWidget::sendDataAll(PortType type, const QByteArray &data) {
  sendData(type, -1, data);
}

void ByteArrayDataWidget::sendDataAll(PortIndex index, const QByteArray &data) {
  sendData(PortType::None, index, data);
}

void ByteArrayDataWidget::sendDataAll(const QByteArray &data) {
  sendData(PortType::None, -1, data);
}

void ByteArrayDataWidget::setWidget(QWidget *widget) {
  m_layout->replaceWidget(m_widget, widget);
  m_widget->deleteLater();
  m_widget = widget;
}

void ByteArrayDataWidget::slot_onInRx() { m_ledInRx->switchOnTimer(); }

void ByteArrayDataWidget::slot_onInTx() { m_ledInTx->switchOnTimer(); }

void ByteArrayDataWidget::slot_onOutRx() { m_ledOutRx->switchOnTimer(); }

void ByteArrayDataWidget::slot_onOutTx() { m_ledOutTx->switchOnTimer(); }
