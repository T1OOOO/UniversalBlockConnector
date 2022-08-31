#include "delaydatamodel.h"

DelayDataModel::DelayDataModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<DelayController>::create();

  registerController(m_controller);
}
