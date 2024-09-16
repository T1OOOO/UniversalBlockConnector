#ifndef STRUCTVIEWERLISTMODEL_H
#define STRUCTVIEWERLISTMODEL_H

#include <qbinarizer/StructDecoder>

#include <QAbstractTableModel>
#include <QPointer>

class StructViewerListModel : public QAbstractTableModel {
  Q_OBJECT
public:
  explicit StructViewerListModel(QObject *parent = nullptr);

  void setDatafield(const QString &datafield);

  void addData(const QByteArray &data);

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent) const override;

  int columnCount(const QModelIndex &parent) const override;

protected:
private:
  QString m_datafiled;
  QPointer<qbinarizer::StructDecoder> m_decoder;
  QList<QVariantList> m_structList;
};

#endif // STRUCTVIEWERLISTMODEL_H
