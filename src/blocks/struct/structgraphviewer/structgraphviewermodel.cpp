#include "structgraphviewermodel.h"

StructGraphViewerModel::StructGraphViewerModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<StructGraphViewerController>::create();

  registerController(m_controller);
}
