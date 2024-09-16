#include "structgraphviewercontroller.h"

StructGraphViewerController::StructGraphViewerController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_widget = new StructGraphViewerWidget();

  registerWidget(m_widget);
}

void StructGraphViewerController::onReceiveData(PortType portType,
                                                PortIndex portIndex,
                                                const QByteArray &data) {
  // if (!m_widget) {
  //   return;
  // }

  // m_widget->addData(data);
}
