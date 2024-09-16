#ifndef STRUCTVIEWERCONTROLLER_H
#define STRUCTVIEWERCONTROLLER_H

#include <QObject>

#include "../../common/bytearraydatacontroller.h"
#include "structviewerwidget.h"

class StructViewerController : public ByteArrayDataController {
  Q_OBJECT
public:
  explicit StructViewerController(QObject *parent = nullptr);

signals:

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<StructViewerWidget> m_widget;
};

#endif // STRUCTVIEWERCONTROLLER_H
