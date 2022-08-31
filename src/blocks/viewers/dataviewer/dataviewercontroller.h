#ifndef DATAVIEWERCONTROLLER_H
#define DATAVIEWERCONTROLLER_H

#include <QObject>

#include "../../common/bytearraydatacontroller.h"
#include "dataviewerwidget.h"

class DataViewerController : public ByteArrayDataController {
  Q_OBJECT
public:
  explicit DataViewerController(QObject *parent = nullptr);

signals:

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<DataViewerWidget> m_widget;
};

#endif // DATAVIEWERCONTROLLER_H
