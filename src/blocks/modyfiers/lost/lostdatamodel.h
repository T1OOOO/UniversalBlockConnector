#ifndef LOSTDATAMODEL_H
#define LOSTDATAMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "lostcontroller.h"

class LostDataModel : public ByteArrayDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  LostDataModel();

  virtual ~LostDataModel() {}

public:
  QString caption() const override { return QStringLiteral("Lost data"); }

  QString name() const override { return QStringLiteral("Lost"); }

signals:
private slots:
protected:
private:
  QSharedPointer<LostController> m_controller;
};

#endif // LOSTDATAMODEL_H
