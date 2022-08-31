#ifndef TCPSERVERMULTIWIDGET_H
#define TCPSERVERMULTIWIDGET_H

#include <QComboBox>
#include <QPointer>
#include <QPushButton>
#include <QSpinBox>
#include <QTableView>

#include "../../common/bytearraydatawidget.h"
#include "sockettabledelegate.h"
#include "sockettablemodel.h"

class TcpServerMultiWidget : public ByteArrayDataWidget {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit TcpServerMultiWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

  SocketTableModel *getModel() const;

  void updateColumnSize();

signals:
  void signal_open(const QString &address, const quint16 port);

  void signal_closeSocket(const int num);

  void signal_close();

public slots:
  void slot_onPush();

  void slot_onOpen();

  void slot_onClose();

  void slot_onError(const QString &str);

  void slot_onCloseSocket(const int num);

private:
  QPointer<QComboBox> m_srcAddress;
  QPointer<QSpinBox> m_srcPort;
  QPointer<QTableView> m_view;
  QPointer<SocketTableModel> m_model;
  QPointer<SocketTableDelegate> m_delegate;

  QPointer<QPushButton> m_open;
};

#endif // TCPSERVERMULTIWIDGET_H
