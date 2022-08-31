#ifndef DATASENDERMODEL_H
#define DATASENDERMODEL_H

#include "../../common/bytearraydatamodel.h"
#include "datasendercontroller.h"
#include <QPointer>

class DataSenderModel : public ByteArrayDataModel {
  Q_OBJECT
public:
  explicit DataSenderModel();

  QString caption() const override;

  QString name() const override;

protected:
signals:
public slots:
private:
  QSharedPointer<DataSenderController> m_controller;
};

#endif // DATASENDERMODEL_H
