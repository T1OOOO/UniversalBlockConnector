#ifndef TCPSERVERDATAMODEL_H
#define TCPSERVERDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "tcpservercontroller.h"

class TcpServerDataModel : public ByteArrayDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  TcpServerDataModel();

  virtual ~TcpServerDataModel() {}

  QString caption() const override { return QStringLiteral("Tcp server"); }

  QString name() const override { return QStringLiteral("TcpServer"); }

private slots:
protected:
private:
  QSharedPointer<TcpServerController> m_controller;
};

#endif // TCPSERVERDATAMODEL_H
