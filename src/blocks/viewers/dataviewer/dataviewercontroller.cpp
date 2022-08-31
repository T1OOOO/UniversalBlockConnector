#include "dataviewercontroller.h"

DataViewerController::DataViewerController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_widget = new DataViewerWidget();

  registerWidget(m_widget);
}

void DataViewerController::onReceiveData(PortType portType, PortIndex portIndex,
                                         const QByteArray &data) {
  if (!m_widget) {
    return;
  }

  m_widget->addData(data);
}
