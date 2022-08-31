#ifndef TCPCLIENTDATAMODEL_H
#define TCPCLIENTDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "tcpclientcontroller.h"

class TcpClientDataModel : public ByteArrayDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  TcpClientDataModel();

  virtual ~TcpClientDataModel() {}

  QString caption() const override { return QStringLiteral("Tcp client"); }

  QString name() const override { return QStringLiteral("TcpClient"); }

signals:
private slots:
protected:
private:
  QSharedPointer<TcpClientController> m_controller;
};

#endif // TCPCLIENTDATAMODEL_H
