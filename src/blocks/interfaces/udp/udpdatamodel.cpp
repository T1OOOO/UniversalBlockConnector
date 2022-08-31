#include "udpdatamodel.h"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

UdpDataModel::UdpDataModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<UdpController>::create();

  registerController(m_controller);
}
