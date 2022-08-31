#ifndef BYTEARRAYDATAWIDGET_H
#define BYTEARRAYDATAWIDGET_H

#include <QGridLayout>
#include <QJsonObject>
#include <QLabel>
#include <QPointer>
#include <QTimer>
#include <QWidget>

#include <nodes/NodeDataModel>

#include "ledwidget.h"
#include "log4qt/logger.h"

using QtNodes::PortIndex;
using QtNodes::PortType;

class ByteArrayDataWidget : public QWidget {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit ByteArrayDataWidget(QWidget *parent = nullptr);

  virtual QJsonObject saveSettings() const = 0;

  virtual void restoreSettings(const QJsonObject &obj) = 0;

  void setTitle(const QString &str);

  void slot_onReceiveData(const QByteArray &data);

signals:
  void signal_sendData(PortType type, PortIndex index, const QByteArray &data);

public slots:
  void slot_onInRx();

  void slot_onInTx();

  void slot_onOutRx();

  void slot_onOutTx();

protected:
  virtual void onReceiveData(const QByteArray &data) {}

  void sendData(PortType type, PortIndex index, const QByteArray &data);

  void sendDataAll(PortType type, const QByteArray &data);

  void sendDataAll(PortIndex index, const QByteArray &data);

  void sendDataAll(const QByteArray &data);

  void setWidget(QWidget *widget);

private:
  QPointer<QLabel> m_title;
  QPointer<LedWidget> m_ledInRx;
  QPointer<LedWidget> m_ledInTx;
  QPointer<LedWidget> m_ledOutRx;
  QPointer<LedWidget> m_ledOutTx;

  QPointer<QGridLayout> m_layout;
  QPointer<QWidget> m_widget;
};

#endif // BYTEARRAYDATAWIDGET_H
