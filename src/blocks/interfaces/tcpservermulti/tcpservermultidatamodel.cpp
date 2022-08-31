#include "tcpservermultidatamodel.h"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

TcpServerMultiDataModel::TcpServerMultiDataModel() : ByteArrayDataModel{} {
  setInPortCount(5);
  setOutPortCount(5);

  m_controller = QSharedPointer<TcpServerMultiController>::create();

  registerController(m_controller);
}
