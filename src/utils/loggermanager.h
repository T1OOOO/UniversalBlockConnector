#ifndef LOGGERMANAGER_H
#define LOGGERMANAGER_H

#include <QObject>

#include "log4qt/logger.h"

class LoggerManager : public QObject {
  Q_OBJECT

public:
  explicit LoggerManager(QObject *parent = nullptr);

  static void init();

  static void deinit();

  static Log4Qt::Logger *log();

private:
  static void initializeRootLogger();

  static void shutdownRootLogger();

  static void logStartup();

  static void logShutdown();

  static void setupRootLogger(const QString &introMessage);

  static void shutDownRootLogger(const QString &extroMessage);

signals:
};

#endif // LOGGERMANAGER_H
