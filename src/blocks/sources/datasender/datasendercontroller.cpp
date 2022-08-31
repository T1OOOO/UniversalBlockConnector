#include "datasendercontroller.h"

DataSenderController::DataSenderController() : ByteArrayDataController{} {
  m_widget = new DataSenderWidget();

  registerWidget(m_widget);
}
