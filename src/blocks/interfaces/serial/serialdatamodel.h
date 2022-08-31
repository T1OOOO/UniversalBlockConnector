#ifndef SERIALDATAMODEL_H
#define SERIALDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "serialcontroller.h"

class SerialDataModel : public ByteArrayDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  SerialDataModel();

  virtual ~SerialDataModel() {}

  QString caption() const override { return QStringLiteral("Serial"); }

  QString name() const override { return QStringLiteral("Serial"); }

signals:
private slots:
protected:
private:
  QSharedPointer<SerialController> m_controller;
};

#endif // SERIALDATAMODEL_H
