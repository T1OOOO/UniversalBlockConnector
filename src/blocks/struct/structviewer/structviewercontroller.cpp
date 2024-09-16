#include "structviewercontroller.h"

StructViewerController::StructViewerController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_widget = new StructViewerWidget();

  registerWidget(m_widget);
}

void StructViewerController::onReceiveData(PortType portType,
                                           PortIndex portIndex,
                                           const QByteArray &data) {
  // if (!m_widget) {
  //   return;
  // }

  // m_widget->addData(data);
}
