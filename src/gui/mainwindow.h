#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
#include <nodes/FlowView>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

signals:

protected:
  void setStyle();

  std::shared_ptr<DataModelRegistry> registerDataModels();

private:
  QPointer<FlowView> m_view;
  QPointer<FlowScene> m_scene;
};

#endif // MAINWINDOW_H
