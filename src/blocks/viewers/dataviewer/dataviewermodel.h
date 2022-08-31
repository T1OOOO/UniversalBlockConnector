#ifndef DATAVIEWERMODEL_H
#define DATAVIEWERMODEL_H

#include <QObject>

#include "../../common/bytearraydatamodel.h"
#include "dataviewercontroller.h"

class DataViewerModel : public ByteArrayDataModel {
  Q_OBJECT

public:
  DataViewerModel();

  virtual ~DataViewerModel() {}

public:
  QString caption() const override { return QStringLiteral("Data Viewer"); }

  QString name() const override { return QStringLiteral("DataViewer"); }

signals:
private slots:
protected:
private:
  QSharedPointer<DataViewerController> m_controller;
};

#endif // DATAVIEWERMODEL_H
