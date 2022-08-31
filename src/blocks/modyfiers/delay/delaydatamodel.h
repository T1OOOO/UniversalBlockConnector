#ifndef DELAYDATAMODEL_H
#define DELAYDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "delaycontroller.h"

class DelayDataModel : public ByteArrayDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  DelayDataModel();

  virtual ~DelayDataModel() {}

public:
  QString caption() const override { return QStringLiteral("Delay data"); }

  QString name() const override { return QStringLiteral("Delay"); }

signals:
private slots:
protected:
private:
  QSharedPointer<DelayController> m_controller;
};

#endif // DATAVIEWERMODEL_H
