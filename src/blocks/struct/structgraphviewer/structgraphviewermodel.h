#ifndef STRUCTGRAPHVIEWERMODEL_H
#define STRUCTGRAPHVIEWERMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "structgraphviewercontroller.h"

class StructGraphViewerModel : public ByteArrayDataModel {
  Q_OBJECT

public:
  StructGraphViewerModel();

  virtual ~StructGraphViewerModel() {}

public:
  QString caption() const override {
    return QStringLiteral("StructGraphViewer");
  }

  QString name() const override { return QStringLiteral("StructGraphViewer"); }

private:
  QSharedPointer<StructGraphViewerController> m_controller;
};

#endif // STRUCTGRAPHVIEWERMODEL_H
