#include "structsenderwidget.h"

#include "../utils/highlighter.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLabel>
#include <QPushButton>

#define TEXT_TIMEOUT 5000
#define TEXT_MAX_SIZE (1024 * 1024 * 1024)

StructSenderWidget::StructSenderWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);
  m_editor = new QTextEdit(widget);
  layout->addWidget(m_editor, 0, 0, 1, 2);

  auto *hightlighter = new Highlighter(m_editor->document());

  auto *apply = new QPushButton("Apply", widget);
  connect(apply, &QPushButton::clicked, this, [this]() {
    const QString datafield = m_editor->toPlainText();
    const auto [data, valueList] = m_encoder->encode(datafield);
    const QString values =
        QJsonDocument(QJsonArray::fromVariantList(valueList)).toJson();

    m_data->setText(data.toHex());
    m_model->loadJson(values.toLatin1());
    m_view->expandAll();
  });
  layout->addWidget(apply, 1, 0, 1, 2);

  m_view = new QTreeView(widget);
  m_model = new QJsonModel(m_view);
  m_view->setModel(m_model);

  layout->addWidget(m_view, 2, 0, 1, 2);

  auto *update = new QPushButton("Update", widget);
  connect(update, &QPushButton::clicked, this, [this]() {
    const QString datafield = m_editor->toPlainText();
    const QString values = m_model->json();
    const auto &[data, valueList] = m_encoder->encode(datafield, values);

    m_data->setText(data.toHex());
  });
  layout->addWidget(update, 3, 0, 1, 2);

  auto *dataLabel = new QLabel("Data: ", widget);
  layout->addWidget(dataLabel, 4, 0);
  m_data = new QLineEdit(widget);
  layout->addWidget(m_data, 4, 1);

  auto *send = new QPushButton("Send", widget);
  connect(send, &QPushButton::clicked, this, [this]() {
    const QString dataStr = m_data->text();
    const QByteArray data = QByteArray::fromHex(dataStr.toLatin1());

    sendDataAll(data);
  });
  layout->addWidget(send, 5, 0, 1, 2);

  m_encoder = new qbinarizer::StructEncoder(this);
}

QJsonObject StructSenderWidget::saveSettings() const {
  QJsonObject obj;
  obj["datafield"] = m_editor->toPlainText();

  return obj;
}

void StructSenderWidget::restoreSettings(const QJsonObject &obj) {
  const QString datafield = obj["datafield"].toString();
  m_editor->setPlainText(datafield);
  // m_model->setDatafield(datafield);
}

void StructSenderWidget::onReceiveData(const QByteArray &data) {
  // m_model->addData(data);
}
