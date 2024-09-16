#include "structsendermodel.h"

StructSenderModel::StructSenderModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<StructSenderController>::create();

  registerController(m_controller);
}
