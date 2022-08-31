#ifndef TCPCLIENTCONTROLLER_H
#define TCPCLIENTCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <QTcpSocket>
#include <QTimer>

#include "../../common/bytearraydatacontroller.h"
#include "tcpclientwidget.h"

class TcpClientController : public ByteArrayDataController {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit TcpClientController(QObject *parent = nullptr);

  bool connectToHost(const QString &clientAddress, const quint16 clientPort);

  void close();

  void write(const QByteArray &data);

signals:
  void signal_open();

  void signal_connecting();

  void signal_close();

  void signal_error(const QString &str);

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

public slots:
  void slot_onConnect(const QString &clientAddress, const quint16 clientPort);

  void slot_onReconnect(const bool reconnect);

  void slot_onClose();

  void slot_onStateChanged(QAbstractSocket::SocketState);

  void slot_onErrorOccurred(QAbstractSocket::SocketError);

  void slot_onReadyRead();

  void slot_onReconnectTimer();

private:
  QPointer<QTcpSocket> m_sock;
  QPointer<TcpClientWidget> m_widget;
  QTimer m_reconnectTimer;

  bool m_reconnect;
  QString m_clientAddress;
  quint16 m_clientPort;
};

#endif // TCPCLIENTCONTROLLER_H
