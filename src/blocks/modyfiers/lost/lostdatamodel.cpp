#include "lostdatamodel.h"

LostDataModel::LostDataModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<LostController>::create();

  registerController(m_controller);
}
