#include "delaycontroller.h"

#include <QDateTime>

namespace {
constexpr qint64 defaultTimeout = 1000;
}

DelayController::DelayController(QObject *parent)
    : ByteArrayDataController{parent}, m_timeout(defaultTimeout) {
  m_widget = new DelayWidget();

  registerWidget(m_widget);

  connect(&m_timer, &QTimer::timeout, this, &DelayController::slot_onTimer);
}

void DelayController::onReceiveData(const QByteArray &data) {
  DelayStruct st;
  st.time = QDateTime::currentMSecsSinceEpoch();
  st.data = data;

  m_delayList.push_back(st);

  if (!m_timer.isActive()) {
    m_timer.start(m_timeout);
  }
}

void DelayController::slot_onTimer() {
  const qint64 timeCurrent = QDateTime::currentMSecsSinceEpoch();

  QMutableListIterator<DelayStruct> iterator(m_delayList);
  while (iterator.hasNext()) {
    auto &st = iterator.next();
    const qint64 timeDiff = timeCurrent - st.time;
    if (timeDiff < defaultTimeout) {
      break;
    }

    sendData(st.data);
    iterator.remove();
  }

  if (!m_delayList.isEmpty()) {
    auto &st = m_delayList.first();
    const qint64 timeDiff = timeCurrent - st.time;
    const qint64 timeout = m_timeout - timeDiff;

    m_timer.start(timeout);
  }
}
