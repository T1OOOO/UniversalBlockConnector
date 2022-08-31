#include "bytearraydatamodel.h"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

namespace {
constexpr int defaultOutCount = 1;
constexpr int defaultInCount = 1;
} // namespace

ByteArrayDataModel::ByteArrayDataModel()
    : NodeDataModel{}, m_uuid(QUuid::createUuid()) {
  setOutPortCount(defaultOutCount);
  setInPortCount(defaultInCount);
}

ByteArrayDataModel::~ByteArrayDataModel() {}

QJsonObject ByteArrayDataModel::save() const {
  QJsonObject modelJson = NodeDataModel::save();

  QJsonObject obj = saveSettings();
  modelJson["settings"] = obj;

  return modelJson;
}

void ByteArrayDataModel::restore(QJsonObject const &p) {
  QJsonValue v = p["settings"];

  if (!v.isUndefined()) {
    const QJsonObject obj = v.toObject();

    restoreSettings(obj);
  }
}

unsigned int ByteArrayDataModel::nPorts(PortType portType) const {
  unsigned int result = 1;

  switch (portType) {
  case PortType::In:
    result = m_inDataList.size();
    break;

  case PortType::Out:
    result = m_outDataList.size();
    break;

  default:
    break;
  }

  return result;
}

void ByteArrayDataModel::slot_onReceiveOutData(const QUuid &uuid,
                                               const QByteArray &data) {
  if (m_uuid == uuid) {
    return;
  }

  auto *dataOut = qobject_cast<ByteArrayData *>(sender());
  if (dataOut == nullptr) {
    return;
  }

  const auto it = std::find_if(
      m_outDataList.cbegin(), m_outDataList.cend(),
      [dataOut](const auto dataP) -> bool { return dataP.get() == dataOut; });
  if (it == m_outDataList.cend()) {
    return;
  }
  const int num = std::distance(m_outDataList.cbegin(), it);

  if (m_dataController) {
    auto dataController = m_dataController.lock();
    if (dataController) {
      dataController->addReceivedData(PortType::Out, num, data);
    }
  }

  receiveData(PortType::Out, num, data);
}

void ByteArrayDataModel::slot_onReceiveInData(const QUuid &uuid,
                                              const QByteArray &data) {
  if (m_uuid == uuid) {
    return;
  }

  auto *dataOut = qobject_cast<ByteArrayData *>(sender());
  if (dataOut == nullptr) {
    return;
  }

  const auto it = std::find_if(m_inDataList.cbegin(), m_inDataList.cend(),
                               [dataOut](const auto inDataWk) -> bool {
                                 const auto inDataSh = inDataWk.lock();
                                 if (!inDataSh) {
                                   return false;
                                 }

                                 return inDataSh.get() == dataOut;
                               });
  if (it == m_inDataList.cend()) {
    return;
  }
  const int num = std::distance(m_inDataList.cbegin(), it);

  if (m_dataController) {
    auto dataController = m_dataController.lock();
    if (dataController) {
      dataController->addReceivedData(PortType::In, num, data);
    }
  }

  receiveData(PortType::In, num, data);
}

void ByteArrayDataModel::slot_onSendDataController(PortType type,
                                                   PortIndex index,
                                                   const QByteArray &data) {
  sendData(type, index, data);
}

void ByteArrayDataModel::sendData(PortType type, PortIndex index,
                                  const QByteArray &data) {
  const bool sendToOut = (type == PortType::Out) || (type == PortType::None);
  const bool sendToIn = (type == PortType::In) || (type == PortType::None);
  const bool sendToAll = (index < 0);

  if (sendToOut) {
    if (!sendToAll && (index > 0) && (index < m_outDataList.size())) {
      m_outDataList[index]->sendData(m_uuid, data);
    } else {
      for (auto &outData : m_outDataList) {
        outData->sendData(m_uuid, data);
      }
    }
  }

  if (sendToIn) {
    if (!sendToAll && (index > 0) && (index < m_inDataList.size())) {
      const auto inDataSh = m_inDataList[index].lock();
      if (inDataSh) {
        inDataSh->sendData(m_uuid, data);
      }
    } else {
      for (const auto &inDataWk : m_inDataList) {
        const auto inDataSh = inDataWk.lock();
        if (inDataSh) {
          inDataSh->sendData(m_uuid, data);
        }
      }
    }
  }
}

void ByteArrayDataModel::sendDataAll(PortType portType,
                                     const QByteArray &data) {
  sendData(portType, -1, data);
}

void ByteArrayDataModel::sendDataAll(PortIndex portIndex,
                                     const QByteArray &data) {
  sendData(PortType::None, portIndex, data);
}

void ByteArrayDataModel::sendDataAll(const QByteArray &data) {
  sendData(PortType::None, -1, data);
}

QJsonObject ByteArrayDataModel::saveSettings() const {
  if (!m_dataController) {
    return {};
  }

  auto dataController = m_dataController.lock();
  if (!dataController) {
    return {};
  }

  return dataController->saveSettings();
}

void ByteArrayDataModel::restoreSettings(const QJsonObject &obj) {
  if (!m_dataController) {
    return;
  }

  auto dataController = m_dataController.lock();
  if (!dataController) {
    return;
  }

  dataController->restoreSettings(obj);
}

NodeDataType ByteArrayDataModel::dataType(PortType, PortIndex) const {
  return ByteArrayData().type();
}

std::shared_ptr<NodeData> ByteArrayDataModel::outData(PortIndex index) {
  if (index >= m_outDataList.size()) {
    return {};
  }

  return m_outDataList[index];
}

void ByteArrayDataModel::setInData(std::shared_ptr<NodeData> data,
                                   PortIndex index) {
  if (index >= m_inDataList.size()) {
    return;
  }

  auto byteArrayData = std::dynamic_pointer_cast<ByteArrayData>(data);
  if (!byteArrayData) {
    auto inData = m_inDataList[index].lock();
    if (inData) {
      inData->disconnect(this);
    }

    inData.reset();
    emit dataInvalidated(0);

    return;
  }

  m_inDataList[index] = byteArrayData;
  connect(byteArrayData.get(), &ByteArrayData::signal_receiveData, this,
          &ByteArrayDataModel::slot_onReceiveInData);
}

QString ByteArrayDataModel::portCaption(PortType type, PortIndex index) const {
  QString name = "Data";

  if (type == PortType::Out) {
    if (index < m_outDataList.size()) {
      name = m_outDataList.at(index)->type().name;
    }

    return QString("%1 %2").arg(name).arg(index);
  }

  if (type == PortType::In) {
    if (index < m_inDataList.size()) {
      const auto inDataSh = m_inDataList.at(index).lock();
      if (inDataSh) {
        name = inDataSh->type().name;
      }
    }

    return QString("%1 %2").arg(index).arg(name);
  }

  return name;
}

bool ByteArrayDataModel::portCaptionVisible(PortType type, PortIndex) const {
  if (type == PortType::Out) {
    return m_outDataList.size() > 1;
  } else if (type == PortType::In) {
    return m_inDataList.size() > 1;
  }

  return false;
}

void ByteArrayDataModel::registerController(
    const QSharedPointer<ByteArrayDataController> &controller) {
  m_dataController = controller;

  connect(controller.get(), &ByteArrayDataController::signal_sendData, this,
          &ByteArrayDataModel::slot_onSendDataController);
}

void ByteArrayDataModel::setInPortCount(const int count) {
  for (auto inDataWk : m_inDataList) {
    const auto inDataSh = inDataWk.lock();
    if (!inDataSh) {
      continue;
    }

    inDataSh->disconnect(this);
  }

  m_inDataList.clear();
  m_inDataList.resize(count);
}

void ByteArrayDataModel::setOutPortCount(const int count) {
  for (auto data : m_outDataList) {
    data->disconnect(this);
  }
  m_outDataList.clear();

  for (int i = 0; i < count; i++) {
    auto data = std::make_shared<ByteArrayData>(m_uuid);
    connect(data.get(), &ByteArrayData::signal_receiveData, this,
            &ByteArrayDataModel::slot_onReceiveOutData);

    m_outDataList.push_back(data);
  }
}
