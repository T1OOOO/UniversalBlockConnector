#ifndef UDPDATAMODEL_H
#define UDPDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "udpcontroller.h"

class UdpDataModel : public ByteArrayDataModel {
  Q_OBJECT

public:
  UdpDataModel();

  virtual ~UdpDataModel() {}

  QString caption() const override { return QStringLiteral("Udp"); }

  QString name() const override { return QStringLiteral("Udp"); }

signals:
private slots:
protected:
private:
  QSharedPointer<UdpController> m_controller;
};

#endif // UDPDATAMODEL_H
