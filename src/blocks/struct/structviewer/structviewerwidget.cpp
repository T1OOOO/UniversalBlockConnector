#include "structviewerwidget.h"

#include "../utils/highlighter.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QScrollBar>

#define TEXT_TIMEOUT 5000
#define TEXT_MAX_SIZE (1024 * 1024 * 1024)

StructViewerWidget::StructViewerWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);
  m_editor = new QTextEdit(widget);
  layout->addWidget(m_editor, 0, 0);

  auto *hightlighter = new Highlighter(m_editor->document());

  auto *apply = new QPushButton("Apply", widget);
  connect(apply, &QPushButton::clicked, this, [this]() {
    const QString datafield = m_editor->toPlainText();

    m_model->setDatafield(datafield);
  });
  layout->addWidget(apply, 1, 0);

  m_table = new QTableView(widget);
  m_model = new StructViewerListModel(m_table);
  m_table->setModel(m_model);

  layout->addWidget(m_table, 2, 0);
}

QJsonObject StructViewerWidget::saveSettings() const {
  QJsonObject obj;
  obj["datafield"] = m_editor->toPlainText();

  return obj;
}

void StructViewerWidget::restoreSettings(const QJsonObject &obj) {
  const QString datafield = obj["datafield"].toString();
  m_editor->setPlainText(datafield);
  m_model->setDatafield(datafield);
}

void StructViewerWidget::onReceiveData(const QByteArray &data) {
  m_model->addData(data);
}
