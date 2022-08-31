#include <nodes/ConnectionStyle>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/NodeData>
#include <nodes/TypeConverter>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>

#include <nodes/DataModelRegistry>

#include <QtGui/QScreen>

#include "src/blocks/interfaces/serial/serialdatamodel.h"
#include "src/blocks/interfaces/tcpclient/tcpclientdatamodel.h"
#include "src/blocks/interfaces/tcpserver/tcpserverdatamodel.h"
#include "src/blocks/interfaces/tcpservermulti/tcpservermultidatamodel.h"
#include "src/blocks/interfaces/udp/udpdatamodel.h"
#include "src/blocks/modyfiers/delay/delaydatamodel.h"
#include "src/blocks/modyfiers/lost/lostdatamodel.h"
#include "src/blocks/sources/datasender/datasendermodel.h"
#include "src/blocks/struct/structsender/structsendermodel.h"
#include "src/blocks/struct/structviewer/structviewermodel.h"
#include "src/blocks/viewers/dataviewer/dataviewermodel.h"

#include "src/utils/loggermanager.h"

using QtNodes::ConnectionStyle;
using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::TypeConverter;
using QtNodes::TypeConverterId;

static std::shared_ptr<DataModelRegistry> registerDataModels() {
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

  ret->registerModel<StructSenderModel>("Struct");

  ret->registerModel<StructViewerModel>("Struct");

  ret->registerModel<DataViewerModel>("Viewers");

  return ret;
}

static void setStyle() {
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

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  LoggerManager::init();

  setStyle();

  QWidget mainWidget;

  auto menuBar = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");

  auto *l = new QVBoxLayout(&mainWidget);

  l->addWidget(menuBar);
  auto *scene = new FlowScene(registerDataModels(), &mainWidget);
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  QObject::connect(saveAction, &QAction::triggered, scene, &FlowScene::save);

  QObject::connect(loadAction, &QAction::triggered, scene, &FlowScene::load);

  mainWidget.setWindowTitle("Dataflow tools: simplest calculator");
  mainWidget.resize(800, 600);
  mainWidget.showNormal();

  return app.exec();
}
