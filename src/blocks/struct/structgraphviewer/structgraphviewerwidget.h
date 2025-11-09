#ifndef STRUCTGRAPHVIEWERWIDGET_H
#define STRUCTGRAPHVIEWERWIDGET_H

#include <QChartView>
#include <QLineEdit>
#include <QPointer>
#include <QTextEdit>
#include <QWidget>

#include "common/bytearraydatawidget.h"
#include "structchart.h"

class StructGraphViewerWidget : public ByteArrayDataWidget {
  Q_OBJECT
public:
  explicit StructGraphViewerWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

  void onReceiveData(const QByteArray &data) override;

signals:

public slots:

private:
  QPointer<QTextEdit> m_editor;
  QPointer<QLineEdit> m_xField;
  QPointer<QLineEdit> m_yField;
  QPointer<QChartView> m_view;
  QPointer<StructChart> m_chart;
};

#endif // STRUCTGRAPHVIEWERWIDGET_H
