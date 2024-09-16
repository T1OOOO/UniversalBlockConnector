#include "structsendercontroller.h"

StructSenderController::StructSenderController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_widget = new StructSenderWidget();

  registerWidget(m_widget);
}

void StructSenderController::onReceiveData(PortType portType,
                                           PortIndex portIndex,
                                           const QByteArray &data) {
  // if (!m_widget) {
  //   return;
  // }

  // m_widget->addData(data);
}
