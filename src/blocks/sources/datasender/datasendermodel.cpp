#include "datasendermodel.h"

DataSenderModel::DataSenderModel() : ByteArrayDataModel{} {
  m_controller = QSharedPointer<DataSenderController>::create();

  registerController(m_controller);
}

QString DataSenderModel::caption() const {
  return QStringLiteral("Data sender source");
}

QString DataSenderModel::name() const {
  return QStringLiteral("DataSenderSource");
}
