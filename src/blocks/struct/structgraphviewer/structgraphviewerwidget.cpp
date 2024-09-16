#include "structgraphviewerwidget.h"

#include "highlighter.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>

#define TEXT_TIMEOUT 5000
#define TEXT_MAX_SIZE (1024 * 1024 * 1024)

StructGraphViewerWidget::StructGraphViewerWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);
  m_editor = new QTextEdit(widget);
  layout->addWidget(m_editor, 0, 0, 1, 2);

  auto *hightlighter = new Highlighter(m_editor->document());

  auto *xFieldLabel = new QLabel("X: ", widget);
  layout->addWidget(xFieldLabel, 1, 0);
  m_xField = new QLineEdit(widget);
  layout->addWidget(m_xField, 1, 1);

  auto *yFieldLabel = new QLabel("Y: ", widget);
  layout->addWidget(yFieldLabel, 2, 0);
  m_yField = new QLineEdit(widget);
  layout->addWidget(m_yField, 2, 1);

  auto *apply = new QPushButton("Apply", widget);
  connect(apply, &QPushButton::clicked, this, [this]() {
    const QString datafield = m_editor->toPlainText();
    const QString xField = m_xField->text();
    const QString yField = m_yField->text();

    m_chart->clear();
    m_chart->setDatafield(datafield);
    m_chart->setXField(xField);
    m_chart->setYField(yField);
  });
  layout->addWidget(apply, 3, 0, 1, 2);

  m_chart = new StructChart();
  m_view = new QChartView(m_chart, widget);
  m_view->setMinimumSize(200, 200);
  layout->addWidget(m_view, 4, 0, 1, 2);
}

QJsonObject StructGraphViewerWidget::saveSettings() const {
  QJsonObject obj;
  obj["datafield"] = m_editor->toPlainText();
  obj["xField"] = m_xField->text();
  obj["yField"] = m_yField->text();

  return obj;
}

void StructGraphViewerWidget::restoreSettings(const QJsonObject &obj) {
  const QString datafield = obj["datafield"].toString();
  m_editor->setPlainText(datafield);

  const QString xField = obj["xField"].toString();
  m_xField->setText(xField);

  const QString yField = obj["yField"].toString();
  m_yField->setText(yField);
}

void StructGraphViewerWidget::onReceiveData(const QByteArray &data) {
  m_chart->addData(data);
}
