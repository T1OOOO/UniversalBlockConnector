#include "structviewermodel.h"

StructViewerModel::StructViewerModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<StructViewerController>::create();

  registerController(m_controller);
}
