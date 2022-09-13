#ifndef STRUCTVIEWERMODEL_H
#define STRUCTVIEWERMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "structviewercontroller.h"

class StructViewerModel : public ByteArrayDataModel {
  Q_OBJECT

public:
  StructViewerModel();

  virtual ~StructViewerModel() {}

public:
  QString caption() const override { return QStringLiteral("StructViewer"); }

  QString name() const override { return QStringLiteral("StructViewer"); }

signals:
private slots:
protected:
private:
  QSharedPointer<StructViewerController> m_controller;
};

#endif // STRUCTVIEWERMODEL_H
