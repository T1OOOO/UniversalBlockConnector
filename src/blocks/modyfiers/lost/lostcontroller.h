#ifndef LOSTCONTROLLER_H
#define LOSTCONTROLLER_H

#include <QObject>
#include <QQueue>
#include <QSet>
#include <QTimer>

#include "../../common/bytearraydatacontroller.h"
#include "lostwidget.h"

class LostController : public ByteArrayDataController {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  explicit LostController(QObject *parent = nullptr);

  void addData(const QByteArray &data);

signals:

public slots:
  void slot_onLostSettings(const LostSettings &settings);

protected:
  void onReceiveData(PortType portType, PortIndex portIndex,
                     const QByteArray &data) override;

  QByteArray lostData(const QByteArray &data, int &packetsCounter,
                      int &dataCounter);
  QVector<int> generateRandomIdx(int size);
  void updateArrays();
  void updateLostSet();

private:
  LostSettings m_settings;

  QSet<int> m_lostSet; /**< Флаги входных потерь */

  int m_dataCounterIn;  /**< Счетчик входных пакетов */
  int m_dataCounterOut; /**< Счетчик выходных пакетов */

  int m_packetsCounterIn;  /**< Счетчик входных пакетов */
  int m_packetsCounterOut; /**< Счетчик выходных пакетов */

private:
  qint64 m_timeout;
  QPointer<LostWidget> m_widget;
  QTimer m_timer;
};

#endif // LOSTCONTROLLER_H
