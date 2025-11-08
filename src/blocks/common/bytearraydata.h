#ifndef BYTEARRAYDATA_H
#define BYTEARRAYDATA_H

#include <QObject>
#include <QUuid>
#include <QtNodes/NodeData>

#include "log4qt/logger.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class ByteArrayData : public QObject, public NodeData {
  Q_OBJECT
  LOG4QT_DECLARE_QCLASS_LOGGER

public:
  ByteArrayData();

  ByteArrayData(const QUuid &uuid);

  QUuid getUuid() const;

  void setUuid(const QUuid &uuid);

  NodeDataType type() const override { return NodeDataType{"data", "Data"}; }

  void sendData(const QUuid &uid, const QByteArray &data);

signals:
  void signal_receiveData(const QUuid &uid, const QByteArray &data);

private:
  QUuid m_uuid;
};

#endif // BYTEARRAYDATA_H
