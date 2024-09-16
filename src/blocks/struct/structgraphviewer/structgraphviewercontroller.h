#ifndef STRUCTGRAPHVIEWERCONTROLLER_H
#define STRUCTGRAPHVIEWERCONTROLLER_H

#include <QObject>

#include "../../common/bytearraydatacontroller.h"
#include "structgraphviewerwidget.h"

class StructGraphViewerController : public ByteArrayDataController {
  Q_OBJECT
public:
  explicit StructGraphViewerController(QObject *parent = nullptr);

signals:

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<StructGraphViewerWidget> m_widget;
};

#endif // STRUCTGRAPHVIEWERCONTROLLER_H
