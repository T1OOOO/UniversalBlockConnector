#ifndef DELAYWIDGET_H
#define DELAYWIDGET_H

#include <QComboBox>
#include <QPointer>
#include <QWidget>

#include "../../common/bytearraydatawidget.h"

class DelayWidget : public ByteArrayDataWidget {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit DelayWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

signals:

public slots:

private:
  QPointer<QComboBox> m_delay;
};

#endif // DELAYWIDGET_H
