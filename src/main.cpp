#include <QApplication>

#include "gui/mainwindow.h"
#include "utils/loggermanager.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  LoggerManager::init();

  MainWindow mw;
  mw.show();

  return app.exec();
}
