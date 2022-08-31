#include "bytearraydatacontroller.h"

ByteArrayDataController::ByteArrayDataController(QObject *parent)
    : QObject{parent} {}

ByteArrayDataController::~ByteArrayDataController() {}

ByteArrayDataWidget *ByteArrayDataController::getWidget() const {
  return m_dataWidget;
}

QJsonObject ByteArrayDataController::saveSettings() const {
  if (!m_dataWidget) {
    return {};
  }

  return m_dataWidget->saveSettings();
}

void ByteArrayDataController::restoreSettings(const QJsonObject &obj) {
  if (!m_dataWidget) {
    return;
  }

  m_dataWidget->restoreSettings(obj);
}

void ByteArrayDataController::sendData(PortType type, PortIndex index,
                                       const QByteArray &data) {
  emit signal_sendData(type, index, data);

  if (type == PortType::In) {
    emit signal_inTx();
  } else if (type == PortType::Out) {
    emit signal_outTx();
  } else {
    emit signal_inTx();
    emit signal_outTx();
  }
}

void ByteArrayDataController::sendDataAll(PortType type,
                                          const QByteArray &data) {
  sendData(type, -1, data);
}

void ByteArrayDataController::sendDataAll(PortIndex index,
                                          const QByteArray &data) {
  sendData(PortType::None, index, data);
}

void ByteArrayDataController::sendDataAll(const QByteArray &data) {
  sendData(PortType::None, -1, data);
}

void ByteArrayDataController::addReceivedData(PortType type, PortIndex index,
                                              const QByteArray &data) {
  if (m_dataWidget) {
    m_dataWidget->slot_onReceiveData(data);
  }

  onReceiveData(type, index, data);

  if (type == PortType::In) {
    emit signal_inRx();
  } else if (type == PortType::Out) {
    emit signal_outRx();
  }
}

void ByteArrayDataController::slot_onSendDataWidget(QtNodes::PortType type,
                                                    QtNodes::PortIndex index,
                                                    const QByteArray &data) {
  sendData(type, index, data);
}

void ByteArrayDataController::registerWidget(ByteArrayDataWidget *widget) {
  m_dataWidget = widget;

  connect(m_dataWidget, &ByteArrayDataWidget::signal_sendData, this,
          &ByteArrayDataController::slot_onSendDataWidget);

  connect(this, &ByteArrayDataController::signal_inRx, m_dataWidget,
          &ByteArrayDataWidget::slot_onInRx);
  connect(this, &ByteArrayDataController::signal_inTx, m_dataWidget,
          &ByteArrayDataWidget::slot_onInTx);
  connect(this, &ByteArrayDataController::signal_outRx, m_dataWidget,
          &ByteArrayDataWidget::slot_onOutRx);
  connect(this, &ByteArrayDataController::signal_outTx, m_dataWidget,
          &ByteArrayDataWidget::slot_onOutTx);
}
