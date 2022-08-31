#include "sockettablemodel.h"

namespace {
constexpr int defaultClientsCount = 5;
}

SocketTableModel::SocketTableModel(QObject *parent)
    : QAbstractTableModel{parent} {
  m_clientList.resize(defaultClientsCount);
}

void SocketTableModel::setClient(const int num, const QString &address,
                                 const quint16 port) {
  if (num >= m_clientList.size()) {
    return;
  }
  m_clientList[num] = ClientStruct(address, port);

  emit dataChanged(index(num, 0), index(num, 3));
}

void SocketTableModel::resetClient(const int num) { setClient(num, "", 0); }

void SocketTableModel::resetAll() {
  for (int i = 0; i < m_clientList.size(); i++) {
    resetClient(i);
  }
}

int SocketTableModel::rowCount(const QModelIndex &parent) const {
  return defaultClientsCount;
}

int SocketTableModel::columnCount(const QModelIndex &parent) const { return 4; }

QVariant SocketTableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (role != Qt::DisplayRole) {
    return {};
  }

  if (orientation != Qt::Horizontal) {
    return {};
  }

  switch (section) {
  case 0:
    return QStringLiteral("Num");
  case 1:
    return QStringLiteral("Close");
  case 2:
    return QStringLiteral("Port");
  case 3:
    return QStringLiteral("Address");
  default:
    break;
  }

  return {};
}

QVariant SocketTableModel::data(const QModelIndex &index, int role) const {
  if (role != Qt::DisplayRole) {
    return {};
  }

  const int row = index.row();
  const int column = index.column();

  if (row >= m_clientList.size()) {
    return {};
  }

  const auto &client = m_clientList[row];
  switch (column) {
  case 0:
    return QString::number(row);
  case 2:
    return QString::number(client.port);
  case 3:
    return client.address;
  default:
    break;
  }

  return {};
}
