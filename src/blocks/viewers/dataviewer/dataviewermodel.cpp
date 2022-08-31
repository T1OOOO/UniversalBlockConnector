#include "dataviewermodel.h"

DataViewerModel::DataViewerModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<DataViewerController>::create();

  registerController(m_controller);
}
