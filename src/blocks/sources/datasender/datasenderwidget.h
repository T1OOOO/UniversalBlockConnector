#ifndef DATASENDERWIDGET_H
#define DATASENDERWIDGET_H

#include <QLineEdit>
#include <QPointer>
#include <QWidget>

#include "common/bytearraydatawidget.h"

class DataSenderWidget : public ByteArrayDataWidget {
  Q_OBJECT
public:
  explicit DataSenderWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

signals:

public slots:
  void slot_onPush();

protected:
private:
  QPointer<QLineEdit> m_text;
};

#endif // DATASENDERWIDGET_H
