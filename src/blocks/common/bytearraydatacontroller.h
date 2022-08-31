#ifndef BYTEARRAYDATACONTROLLER_H
#define BYTEARRAYDATACONTROLLER_H

#include <QObject>
#include <QPointer>

#include "bytearraydatawidget.h"
#include "log4qt/logger.h"

#include <nodes/NodeDataModel>

using QtNodes::PortIndex;
using QtNodes::PortType;

class ByteArrayDataController : public QObject {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit ByteArrayDataController(QObject *parent = nullptr);

  ~ByteArrayDataController() override;

  ByteArrayDataWidget *getWidget() const;

  virtual QJsonObject saveSettings() const;

  virtual void restoreSettings(const QJsonObject &obj);

  void addReceivedData(PortType type, PortIndex index, const QByteArray &data);

signals:
  void signal_sendData(PortType type, PortIndex index, const QByteArray &data);

  void signal_inRx();

  void signal_inTx();

  void signal_outRx();

  void signal_outTx();

public slots:
  void slot_onSendDataWidget(PortType type, PortIndex index,
                             const QByteArray &data);

protected:
  void sendData(PortType type, PortIndex index, const QByteArray &data);

  void sendDataAll(PortType type, const QByteArray &data);

  void sendDataAll(PortIndex index, const QByteArray &data);

  void sendDataAll(const QByteArray &data);

  void registerWidget(ByteArrayDataWidget *widget);

  virtual void onReceiveData(PortType portType, PortIndex portIndex,
                             const QByteArray &data) {
    if (!m_dataWidget) {
      return;
    }

    m_dataWidget->slot_onReceiveData(data);
  };

private:
  QPointer<ByteArrayDataWidget> m_dataWidget;
};

#endif // BYTEARRAYDATACONTROLLER_H
