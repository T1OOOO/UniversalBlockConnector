#ifndef DATAVIEWERWIDGET_H
#define DATAVIEWERWIDGET_H

#include <QElapsedTimer>
#include <QPlainTextEdit>
#include <QPointer>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

#include "../../common/bytearraydatawidget.h"

class DataViewerWidget : public ByteArrayDataWidget {
  Q_OBJECT
public:
  explicit DataViewerWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

  void addData(const QByteArray &data);

signals:

public slots:

private:
  QElapsedTimer m_timer;

  QPointer<QRadioButton> m_hexMode;
  QPointer<QRadioButton> m_stringMode;
  QPointer<QPushButton> m_pauseButton;
  QPointer<QPushButton> m_clearButton;

  QPointer<QPlainTextEdit> m_view;
};

#endif // DATAVIEWERWIDGET_H
