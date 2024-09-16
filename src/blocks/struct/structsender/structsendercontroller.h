#ifndef STRUCTSENDERCONTROLLER_H
#define STRUCTSENDERCONTROLLER_H

#include <QObject>

#include "../../common/bytearraydatacontroller.h"
#include "structsenderwidget.h"

class StructSenderController : public ByteArrayDataController {
  Q_OBJECT
public:
  explicit StructSenderController(QObject *parent = nullptr);

signals:

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<StructSenderWidget> m_widget;
};

#endif // STRUCTSENDERCONTROLLER_H
