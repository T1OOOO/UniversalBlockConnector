#ifndef BYTEARRAYDATAMODEL_H
#define BYTEARRAYDATAMODEL_H

#include <QLineEdit>
#include <QObject>
#include <QUuid>

#include <nodes/NodeDataModel>

#include "bytearraydata.h"
#include "bytearraydatacontroller.h"

using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;
using QtNodes::PortIndex;
using QtNodes::PortType;

class ByteArrayDataModel : public NodeDataModel {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  ByteArrayDataModel();

  virtual ~ByteArrayDataModel() override;

public:
  QString caption() const override { return QStringLiteral("Data"); }

  bool captionVisible() const override { return true; }

  QString name() const override { return QStringLiteral("Data"); }

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, PortIndex) override;

  QString portCaption(PortType, PortIndex) const override;

  bool portCaptionVisible(PortType, PortIndex) const override;

  ConnectionPolicy portInConnectionPolicy(PortIndex) const override;

  QWidget *embeddedWidget() override {
    if (!m_dataController) {
      return nullptr;
    }

    auto dataController = m_dataController.lock();
    if (!dataController) {
      return nullptr;
    }

    QWidget *widget = dataController->getWidget();

    return widget;
  };

public slots:
  void slot_onReceiveOutData(const QUuid &uuid, const QByteArray &data);

  void slot_onReceiveInData(const QUuid &uuid, const QByteArray &data);

  void slot_onSendDataController(PortType type, PortIndex index,
                                 const QByteArray &data);

protected:
  void sendData(PortType portType, PortIndex portIndex, const QByteArray &data);

  void sendDataAll(PortType portType, const QByteArray &data);

  void sendDataAll(PortIndex portIndex, const QByteArray &data);

  void sendDataAll(const QByteArray &data);

  virtual QJsonObject saveSettings() const;

  virtual void restoreSettings(const QJsonObject &obj);

  virtual void receiveData(PortType portType, PortIndex portIndex,
                           const QByteArray &data){};

  void
  registerController(const QSharedPointer<ByteArrayDataController> &controller);

  void setInPortCount(const int count);

  void setOutPortCount(const int count);

private:
  QUuid m_uuid;
  QVector<std::shared_ptr<ByteArrayData>> m_outDataList;
  QVector<std::weak_ptr<ByteArrayData>> m_inDataList;
  QWeakPointer<ByteArrayDataController> m_dataController;
};
#endif // BYTEARRAYDATAMODEL_H
