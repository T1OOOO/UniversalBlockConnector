#include "delaywidget.h"

#include <QGridLayout>
#include <QLabel>

DelayWidget::DelayWidget(QWidget *parent) : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  auto *delayLabel = new QLabel("Delay: ", widget);
  layout->addWidget(delayLabel, 0, 0);
  m_delay = new QComboBox(widget);
  m_delay->setEditable(true);
  const QList<int> delayList = {1, 50, 100, 250, 500, 1000, 2000, 5000};
  for (const auto delay : delayList) {
    m_delay->addItem(QString::number(delay));
  }
  layout->addWidget(m_delay, 0, 1);
}

QJsonObject DelayWidget::saveSettings() const {
  QJsonObject obj;
  obj["delay"] = m_delay->currentText().toInt();

  return obj;
}

void DelayWidget::restoreSettings(const QJsonObject &obj) {
  m_delay->setCurrentText(QString::number(obj["delay"].toInt()));
}
