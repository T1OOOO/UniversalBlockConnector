#ifndef STRUCTSENDERMODEL_H
#define STRUCTSENDERMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "structsendercontroller.h"

class StructSenderModel : public ByteArrayDataModel {
  Q_OBJECT

public:
  StructSenderModel();

  virtual ~StructSenderModel() {}

public:
  QString caption() const override { return QStringLiteral("StructSender"); }

  QString name() const override { return QStringLiteral("StructSender"); }

signals:
private slots:
protected:
private:
  QSharedPointer<StructSenderController> m_controller;
};

#endif // STRUCTSENDERMODEL_H
