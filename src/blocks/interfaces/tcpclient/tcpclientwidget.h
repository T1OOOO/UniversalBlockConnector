#ifndef TCPCLIENTWIDGET_H
#define TCPCLIENTWIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QPointer>
#include <QPushButton>
#include <QSpinBox>

#include "common/bytearraydatawidget.h"

class TcpClientWidget : public ByteArrayDataWidget {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit TcpClientWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

signals:
  void signal_connect(const QString &clientAddress, const quint16 clientPort);

  void signal_reconnect(const bool reconnect);

  void signal_close();

public slots:
  void slot_onPush();

  void slot_onOpen();

  void slot_onClose();

  void slot_onError(const QString &str);

private:
  QPointer<QComboBox> m_srcAddress;
  QPointer<QSpinBox> m_srcPort;

  QPointer<QComboBox> m_clientAddress;
  QPointer<QSpinBox> m_clientPort;

  QPointer<QCheckBox> m_reconnect;

  QPointer<QPushButton> m_open;
};

#endif // TCPCLIENTWIDGET_H
