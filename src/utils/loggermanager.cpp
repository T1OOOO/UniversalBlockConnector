#include "loggermanager.h"

#include "log4qt/consoleappender.h"
#include "log4qt/fileappender.h"
#include "log4qt/loggerrepository.h"
#include "log4qt/logmanager.h"
#include "log4qt/ttcclayout.h"

#include <QCoreApplication>

LoggerManager::LoggerManager(QObject *parent) : QObject{parent} {}

void LoggerManager::init() { initializeRootLogger(); }

void LoggerManager::deinit() { shutdownRootLogger(); }

Log4Qt::Logger *LoggerManager::log() { return Log4Qt::Logger::rootLogger(); }

void LoggerManager::initializeRootLogger() {
  setupRootLogger(QStringLiteral("Root logger is setup."));
}

void LoggerManager::shutdownRootLogger() {
  shutDownRootLogger(QStringLiteral("Root logger was shutdown."));
}

void LoggerManager::logStartup() {
  auto *logger = log();

  logger->info(QStringLiteral(
      "################################################################"));
  logger->info(QStringLiteral(
      "#                          START                               #"));
  logger->info(QStringLiteral(
      "################################################################"));
}

void LoggerManager::logShutdown() {
  auto logger = Log4Qt::Logger::rootLogger();

  logger->info(QStringLiteral(
      "################################################################"));
  logger->info(QStringLiteral(
      "#                          STOP                                #"));
  logger->info(QStringLiteral(
      "################################################################"));
}

void LoggerManager::setupRootLogger(const QString &introMessage) {
  // Create a layout
  auto *logger = log();

  auto *layout = new Log4Qt::TTCCLayout();
  layout->setName(QStringLiteral("My Layout"));
  layout->activateOptions();
  // Create a console appender
  auto *consoleAppender = new Log4Qt::ConsoleAppender(
      layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
  consoleAppender->setName(QStringLiteral("My Appender"));
  consoleAppender->activateOptions();
  // Add appender on root logger
  logger->addAppender(consoleAppender);
  // Create a file appender

  auto *fileAppender = new Log4Qt::FileAppender(
      layout, QCoreApplication::applicationDirPath() + "/basic.log", true);
  fileAppender->setName(QStringLiteral("My file appender"));
  fileAppender->activateOptions();
  // Add appender on root logger
  logger->addAppender(fileAppender);

  // Set level to info
  logger->setLevel(Log4Qt::Level::DEBUG_INT);
  // Enable handling of Qt messages
  Log4Qt::LogManager::setHandleQtMessages(true);

  if (!introMessage.isEmpty()) {
    logger->info(introMessage);
  }

  qWarning("Handling Qt messages is enabled");
}

void LoggerManager::shutDownRootLogger(const QString &extroMessage) {
  auto *logger = log();

  if (!extroMessage.isEmpty())
    logger->info(extroMessage);
  logger->removeAllAppenders();
  logger->loggerRepository()->shutdown();
}
