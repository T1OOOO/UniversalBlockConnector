#include "bytearraydata.h"

ByteArrayData::ByteArrayData() : ByteArrayData(QUuid::createUuid()) {}

ByteArrayData::ByteArrayData(const QUuid &uuid) : m_uuid(uuid) {}

QUuid ByteArrayData::getUuid() const { return m_uuid; }

void ByteArrayData::setUuid(const QUuid &uuid) { m_uuid = uuid; }

void ByteArrayData::sendData(const QUuid &uuid, const QByteArray &data) {
  emit signal_receiveData(uuid, data);
}
