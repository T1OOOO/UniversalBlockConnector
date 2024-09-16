#include "structviewerlistmodel.h"

StructViewerListModel::StructViewerListModel(QObject *parent)
    : QAbstractTableModel{parent} {
  m_decoder = new qbinarizer::StructDecoder(this);
}

void StructViewerListModel::setDatafield(const QString &datafield) {
  beginResetModel();
  m_datafiled = datafield;
  m_structList.clear();
  endResetModel();
}

void StructViewerListModel::addData(const QByteArray &data) {
  const QVariantList valueList = m_decoder->decode(m_datafiled, data);
  QVariantList extractedValueList =
      qbinarizer::StructDecoder::extractValues(valueList);

  const bool firstStuct = m_structList.isEmpty();
  if (firstStuct) {
    beginResetModel();
  } else {
    beginInsertRows(index(m_structList.size(), 0), m_structList.size(),
                    m_structList.size());
  }

  m_structList.push_back(extractedValueList);

  if (firstStuct) {
    endResetModel();
  } else {
    endInsertRows();
  }
}

QVariant StructViewerListModel::headerData(int section,
                                           Qt::Orientation orientation,
                                           int role) const {
  if (role != Qt::DisplayRole) {
    return {};
  }

  if (orientation == Qt::Vertical) {
    return QString::number(section);
  }

  if (m_structList.isEmpty()) {
    return {};
  }

  const QVariantList &valueList = m_structList.first();
  if (section >= valueList.size()) {
    return {};
  }

  const QVariantMap &valueMap = valueList.at(section).toMap();
  if (valueMap.isEmpty()) {
    return {};
  }

  const QString &key = valueMap.firstKey();

  return key;
}

QVariant StructViewerListModel::data(const QModelIndex &index, int role) const {
  const int row = index.row();
  const int column = index.column();

  if (role != Qt::DisplayRole) {
    return {};
  }

  if (row >= m_structList.size()) {
    return {};
  }

  const QVariantList &valueList = m_structList.at(row);
  if (column >= valueList.size()) {
    return {};
  }

  QVariantMap valueMap = valueList.at(column).toMap();
  if (valueMap.isEmpty()) {
    return {};
  }

  const QString &firstKey = valueMap.firstKey();
  QVariant value = valueMap[firstKey];

  return value;
}

int StructViewerListModel::rowCount(const QModelIndex &parent) const {
  return m_structList.size();
}

int StructViewerListModel::columnCount(const QModelIndex &parent) const {
  if (m_structList.isEmpty()) {
    return 0;
  }

  const QVariantList &firstStruct = m_structList.first();
  int count = firstStruct.size();

  return count;
}
