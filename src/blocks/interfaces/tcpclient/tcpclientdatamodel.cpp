#include "tcpclientdatamodel.h"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

TcpClientDataModel::TcpClientDataModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<TcpClientController>::create();

  registerController(m_controller);
}
