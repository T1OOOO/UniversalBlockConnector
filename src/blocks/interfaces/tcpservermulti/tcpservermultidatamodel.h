#ifndef TCPSERVERMULTIDATAMODEL_H
#define TCPSERVERMULTIDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "tcpservermulticontroller.h"

class TcpServerMultiDataModel : public ByteArrayDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  TcpServerMultiDataModel();

  virtual ~TcpServerMultiDataModel() {}

  QString caption() const override {
    return QStringLiteral("Tcp multi server");
  }

  QString name() const override { return QStringLiteral("TcpServerMulti"); }

private slots:
protected:
private:
  QSharedPointer<TcpServerMultiController> m_controller;
};

#endif // TCPSERVERMULTIDATAMODEL_H
