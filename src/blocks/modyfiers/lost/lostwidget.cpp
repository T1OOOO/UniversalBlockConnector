#include "lostwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

LostWidget::LostWidget(QWidget *parent) : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  auto *modeLabel = new QLabel(tr("Mode: "), widget);
  layout->addWidget(modeLabel, 0, 0);
  m_mode = new QComboBox(widget);
  m_mode->addItem(tr("Packets"), LM_PACKET);
  m_mode->addItem(tr("Stream"), LM_STREAM);
  layout->addWidget(m_mode, 0, 1);

  m_sampleLabel = new QLabel(tr("Sample count: "), widget);
  layout->addWidget(m_sampleLabel, 1, 0);
  m_sample = new QSpinBox(widget);
  m_sample->setSingleStep(1);
  m_sample->setRange(1, 1024 * 1024);
  m_sample->setValue(1000);
  layout->addWidget(m_sample, 1, 1);

  auto *lostCountLabel = new QLabel(tr("Lost count: "), widget);
  layout->addWidget(lostCountLabel, 3, 0);
  m_lost = new QSpinBox(this);
  m_lost->setSingleStep(1);
  m_lost->setRange(0, 1024 * 1024);
  m_lost->setValue(10);
  layout->addWidget(m_lost, 3, 1);

  auto *applyButton = new QPushButton("Apply", widget);
  connect(applyButton, &QPushButton::clicked, this, [this]() {
    LostSettings settings;
    settings.mode = m_mode->currentData().value<LostMode>();
    settings.samples = m_sample->value();

    emit signal_settings(settings);
  });
  layout->addWidget(applyButton, 4, 0, 1, 2);
}

QJsonObject LostWidget::saveSettings() const {
  QJsonObject obj;
  obj["mode"] = m_mode->currentIndex();
  obj["lost"] = m_lost->value();
  obj["sample"] = m_sample->value();

  return obj;
}

void LostWidget::restoreSettings(const QJsonObject &obj) {
  m_mode->setCurrentIndex(obj["mode"].toInt());
  m_lost->setValue(obj["lost"].toDouble(10.0));
  m_sample->setValue(obj["sample"].toInt(1000));
}
