#include "lostcontroller.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <algorithm>
#include <random>

LostController::LostController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_widget = new LostWidget();
  connect(m_widget, &LostWidget::signal_settings, this,
          &LostController::slot_onLostSettings);

  registerWidget(m_widget);
}

void LostController::onReceiveData(PortType portType, PortIndex portIndex,
                                   const QByteArray &data) {
  if (portType == PortType::Out) {
    lostData(data, m_packetsCounterOut, m_dataCounterOut);
  } else if (portType == PortType::In) {
    lostData(data, m_packetsCounterIn, m_dataCounterIn);
  }
}

void LostController::slot_onLostSettings(const LostSettings &settings) {
  m_settings = settings;
}

QByteArray LostController::lostData(const QByteArray &data, int &packetsCounter,
                                    int &dataCounter) {
  if (m_settings.mode == LM_PACKET) {
    if (!m_lostSet.contains(packetsCounter)) {
      return data;
    }

    packetsCounter++;
    packetsCounter %= m_settings.samples;

    if (packetsCounter == 0) {
      updateLostSet();
    }
  } else if (m_settings.mode == LM_STREAM) {
    QByteArray res;
    res.reserve(data.size());

    for (int i = 0; i < data.size(); i++) {
      if (!m_lostSet.contains(dataCounter)) {
        res.push_back(data[i]);
      }

      dataCounter++;
      dataCounter %= m_settings.samples;

      if (dataCounter == 0) {
        updateLostSet();
      }

      return res;
    }
  }

  return {};
}

void LostController::updateArrays() {
  m_packetsCounterIn = 0;
  m_packetsCounterOut = 0;
  m_dataCounterIn = 0;
  m_dataCounterOut = 0;

  updateLostSet();
}

QVector<int> LostController::generateRandomIdx(int size) {
  const quint32 seed = QRandomGenerator::global()->generate();

  QVector<int> randomIdxVec(size, 0);
  std::iota(randomIdxVec.begin(), randomIdxVec.end(), 0);
  std::shuffle(randomIdxVec.begin(), randomIdxVec.end(),
               std::default_random_engine(seed));

  return randomIdxVec;
}

void LostController::updateLostSet() {
  const QVector<int> randomIdx = generateRandomIdx(m_settings.samples);
  const int lostSize =
      m_settings.samples * (static_cast<double>(m_settings.lost) /
                            static_cast<double>(m_settings.samples));

  const QList<int> randomList = randomIdx.mid(0, lostSize).toList();
  m_lostSet = QSet<int>(randomList.cbegin(), randomList.cend());
}
