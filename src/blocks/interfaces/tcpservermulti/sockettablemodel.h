#ifndef SOCKETTABLEMODEL_H
#define SOCKETTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

struct ClientStruct {
  QString address;
  quint16 port;

  ClientStruct() : port(0) {}
  ClientStruct(const QString &address, const quint16 &port)
      : address(address), port(port) {}
};

class SocketTableModel : public QAbstractTableModel {
  Q_OBJECT
public:
  explicit SocketTableModel(QObject *parent = nullptr);

  void setClient(const int num, const QString &address, const quint16 port);

  void resetClient(const int num);

  void resetAll();

  int rowCount(const QModelIndex &parent) const override;

  int columnCount(const QModelIndex &parent) const override;

  QVariant data(const QModelIndex &index, int role) const override;

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

signals:

private:
  QVector<ClientStruct> m_clientList;
};

#endif // SOCKETTABLEMODEL_H
