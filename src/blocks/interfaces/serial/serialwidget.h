#ifndef SERIALWIDGET_H
#define SERIALWIDGET_H

#include <QComboBox>
#include <QLineEdit>
#include <QPointer>
#include <QPushButton>
#include <QSpinBox>
#include <QtSerialPort/QSerialPort>

#include "common/bytearraydatawidget.h"

struct SerialSettings {
  QString port;
  qint32 baudRate;
  QSerialPort::DataBits dataBits;
  QSerialPort::Parity parity;
  QSerialPort::StopBits stopBits;
  QSerialPort::FlowControl flowControl;

  SerialSettings()
      : dataBits(QSerialPort::Data8), parity(QSerialPort::NoParity),
        stopBits(QSerialPort::OneStop),
        flowControl(QSerialPort::NoFlowControl) {}
};
Q_DECLARE_METATYPE(SerialSettings)

class SerialWidget : public ByteArrayDataWidget {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit SerialWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

signals:
  void signal_open(const SerialSettings &settings);

  void signal_clientParams(const QString &address, const quint16 port);

  void signal_close();

public slots:
  void slot_onPush();

  void slot_onOpen();

  void slot_onClose();

  void slot_onError(const QString &str);

private:
  QPointer<QComboBox> m_port;
  QPointer<QComboBox> m_baudRate;
  QPointer<QComboBox> m_dataBits;
  QPointer<QComboBox> m_parity;
  QPointer<QComboBox> m_stopBits;
  QPointer<QComboBox> m_flowControl;

  QPointer<QPushButton> m_open;
};

#endif // SERIALWIDGET_H
