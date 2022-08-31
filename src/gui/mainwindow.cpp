#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include <QScreen>
#include <QVBoxLayout>

#include <nodes/ConnectionStyle>
#include <nodes/NodeData>
#include <nodes/TypeConverter>

#include "interfaces/serial/serialdatamodel.h"
#include "interfaces/tcpclient/tcpclientdatamodel.h"
#include "interfaces/tcpserver/tcpserverdatamodel.h"
#include "interfaces/tcpservermulti/tcpservermultidatamodel.h"
#include "interfaces/udp/udpdatamodel.h"
#include "modyfiers/delay/delaydatamodel.h"
#include "modyfiers/lost/lostdatamodel.h"
#include "sources/datasender/datasendermodel.h"
//#include "struct/structsender/structsendermodel.h"
//#include "struct/structviewer/structviewermodel.h"
//#include "struct/structviewer/structviewermodel.h"
#include "viewers/dataviewer/dataviewermodel.h"

using QtNodes::ConnectionStyle;
using QtNodes::TypeConverter;
using QtNodes::TypeConverterId;

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
  setStyle();

  auto *widget = new QWidget(this);
  setCentralWidget(widget);

  auto *layout = new QVBoxLayout(widget);

  m_view = new FlowView(widget);
  m_scene = new FlowScene(registerDataModels(), m_view);
  m_view->setScene(m_scene);
  layout->addWidget(m_view);

  auto *menu = menuBar();
  auto *fileMenu = menu->addMenu("File");
  auto *saveAction = fileMenu->addAction("Save...");
  connect(saveAction, &QAction::triggered, m_scene, &FlowScene::save);
  auto *loadAction = fileMenu->addAction("Load...");
  connect(loadAction, &QAction::triggered, m_scene, &FlowScene::load);
  auto *exitAction = fileMenu->addAction("Exit");
  connect(exitAction, &QAction::triggered, this,
          []() { QApplication::exit(0); });

  setWindowTitle("UniversalBlockConnector");
  resize(1024, 768);
}

std::shared_ptr<DataModelRegistry> MainWindow::registerDataModels() {
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<DataSenderModel>("Sources");

  ret->registerModel<UdpDataModel>("Interfaces");

  ret->registerModel<TcpServerDataModel>("Interfaces");

  ret->registerModel<TcpServerMultiDataModel>("Interfaces");

  ret->registerModel<TcpClientDataModel>("Interfaces");

  ret->registerModel<TcpClientDataModel>("Interfaces");

  ret->registerModel<SerialDataModel>("Interfaces");

  ret->registerModel<DelayDataModel>("Modyfiers");

  ret->registerModel<LostDataModel>("Modyfiers");

  //  ret->registerModel<StructSenderModel>("Struct");

  //  ret->registerModel<StructViewerModel>("Struct");

  ret->registerModel<DataViewerModel>("Viewers");

  return ret;
}

void MainWindow::setStyle() {
  ConnectionStyle::setConnectionStyle(
      R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}
