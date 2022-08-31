#include "serialdatamodel.h"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

SerialDataModel::SerialDataModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<SerialController>::create();

  registerController(m_controller);
}
