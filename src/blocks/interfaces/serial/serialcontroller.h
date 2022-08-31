#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <QtSerialPort/QSerialPort>

#include "../../common/bytearraydatacontroller.h"
#include "serialwidget.h"

class SerialController : public ByteArrayDataController {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit SerialController(QObject *parent = nullptr);

  ~SerialController() override;

  bool open(const SerialSettings &settings);

  void close();

  void write(const QByteArray &data);

signals:
  void signal_open();

  void signal_close();

  void signal_error(const QString &str);

public slots:
  void slot_onOpen(const SerialSettings &settings);

  void slot_onClose();

  void slot_onErrorOccurred(QSerialPort::SerialPortError error);

  void slot_onReadyRead();

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<QSerialPort> m_sock;
  QPointer<SerialWidget> m_widget;

  QString m_clientAddress;
  quint16 m_clientPort;
};

#endif // SERIALCONTROLLER_H
