#include "datasenderwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

DataSenderWidget::DataSenderWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  auto *textLabel = new QLabel("Text: ", widget);
  layout->addWidget(textLabel, 0, 0);
  m_text = new QLineEdit("test", widget);
  layout->addWidget(m_text, 0, 1);
  auto *sendButton = new QPushButton("Send", widget);
  connect(sendButton, &QPushButton::clicked, this,
          &DataSenderWidget::slot_onPush);
  layout->addWidget(sendButton, 0, 2);
}

QJsonObject DataSenderWidget::saveSettings() const {
  QJsonObject obj;
  obj["text"] = m_text->text();

  return obj;
}

void DataSenderWidget::restoreSettings(const QJsonObject &obj) {
  m_text->setText(obj["text"].toString());
}

void DataSenderWidget::slot_onPush() {
  const QString str = m_text->text();
  const QByteArray data = str.toLatin1();

  sendDataAll(data);
}
