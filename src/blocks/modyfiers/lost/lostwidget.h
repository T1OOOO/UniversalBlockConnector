#ifndef LOSTWIDGET_H
#define LOSTWIDGET_H

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPointer>
#include <QSpinBox>
#include <QWidget>

#include "../../common/bytearraydatawidget.h"

enum LostMode { LM_PACKET = 0, LM_STREAM, LM_SIZE };

struct LostSettings {
  LostMode mode;
  int samples;
  int lost;

  LostSettings() : mode(LM_PACKET), samples(0), lost(0.0) {}
};
Q_DECLARE_METATYPE(LostSettings)

class LostWidget : public ByteArrayDataWidget {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit LostWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

signals:
  void signal_settings(const LostSettings &settings);

public slots:

private:
  QPointer<QComboBox> m_mode;
  QPointer<QSpinBox> m_sample;
  QPointer<QSpinBox> m_lost;
  QLabel *m_sampleLabel;
};

#endif // LOSTWIDGET_H
