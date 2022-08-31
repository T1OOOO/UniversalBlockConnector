#ifndef TCPSERVERCONTROLLER_H
#define TCPSERVERCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <QTcpServer>
#include <QTcpSocket>

#include "../../common/bytearraydatacontroller.h"
#include "tcpserverwidget.h"

class TcpServerController : public ByteArrayDataController {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit TcpServerController(QObject *parent = nullptr);

  ~TcpServerController() override;

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

  void slot_onClose();

  void slot_onNewConnection();

  void slot_onStateChanged(QAbstractSocket::SocketState);

  void slot_onErrorOccurred(QAbstractSocket::SocketError);

  void slot_onReadyRead();

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

private:
  QPointer<QTcpServer> m_server;
  QList<QTcpSocket *> m_clientList;
  QPointer<TcpServerWidget> m_widget;
};

#endif // TCPSERVERCONTROLLER_H
