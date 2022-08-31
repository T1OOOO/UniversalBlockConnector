#ifndef UDPCONTROLLER_H
#define UDPCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <QUdpSocket>

#include "../../common/bytearraydatacontroller.h"
#include "udpwidget.h"

class UdpController : public ByteArrayDataController {
  Q_OBJECT
public:
  explicit UdpController(QObject *parent = nullptr);
  ~UdpController() override;

  bool open(const QString &address, const qint16 port);

  void close();

  void write(const QByteArray &data);

signals:
  void signal_open();

  void signal_close();

  void signal_error(const QString &str);

  void signal_data(const QByteArray &data);

public slots:
  void slot_onOpen(const QString &address, const quint16 port);

  void slot_onClientParams(const QString &address, const quint16 port);

  void slot_onClose();

  void slot_onStateChanged(QAbstractSocket::SocketState);

  void slot_onErrorOccurred(QAbstractSocket::SocketError);

  void slot_onReadyRead();

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<QUdpSocket> m_sock;
  QPointer<UdpWidget> m_widget;

  QString m_clientAddress;
  quint16 m_clientPort;
};

#endif // UDPCONTROLLER_H
