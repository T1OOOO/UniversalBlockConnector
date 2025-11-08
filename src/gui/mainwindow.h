#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeDelegateModelRegistry>

using QtNodes::DataFlowGraphModel;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

signals:

protected:
  void setStyle();

  std::shared_ptr<NodeDelegateModelRegistry> registerDataModels();

private:
  std::shared_ptr<DataFlowGraphModel> m_graphModel;
  QPointer<GraphicsView> m_view;
  QPointer<DataFlowGraphicsScene> m_scene;
};

#endif // MAINWINDOW_H
