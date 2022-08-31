#ifndef DELAYCONTROLLER_H
#define DELAYCONTROLLER_H

#include <QObject>
#include <QQueue>
#include <QTimer>

#include "../../common/bytearraydatacontroller.h"
#include "delaywidget.h"

struct DelayStruct {
  qint64 time;
  QByteArray data;
};

class DelayController : public ByteArrayDataController {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit DelayController(QObject *parent = nullptr);

  void addData(const QByteArray &data);

signals:

public slots:
  void slot_onTimer();

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  qint64 m_timeout;
  QPointer<DelayWidget> m_widget;
  QList<DelayStruct> m_delayList;
  QTimer m_timer;
};

#endif // DELAYCONTROLLER_H
