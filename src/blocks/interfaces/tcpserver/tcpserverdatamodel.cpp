#include "tcpserverdatamodel.h"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

TcpServerDataModel::TcpServerDataModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<TcpServerController>::create();

  registerController(m_controller);
}
