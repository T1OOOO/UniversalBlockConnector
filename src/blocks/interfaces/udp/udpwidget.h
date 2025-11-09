#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include <QComboBox>
#include <QPointer>
#include <QPushButton>
#include <QSpinBox>

#include "common/bytearraydatawidget.h"

class UdpWidget : public ByteArrayDataWidget {
  Q_OBJECT
public:
  explicit UdpWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

signals:
  void signal_open(const QString &address, const quint16 port);

  void signal_clientParams(const QString &address, const quint16 port);

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

  QPointer<QPushButton> m_open;
};

#endif // UDPWIDGET_H
