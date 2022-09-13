#ifndef STRUCTCHART_H
#define STRUCTCHART_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

#include <qbinarizer/ExprMaster>
#include <qbinarizer/StructDecoder>

class StructChart : public QChart {
  Q_OBJECT
public:
  explicit StructChart(QGraphicsItem *parent = nullptr,
                       Qt::WindowFlags wFlags = Qt::WindowFlags());

  void setXField(const QString &name);

  void setYField(const QString &name);

  void setDatafield(const QString &datafield);

  void addData(const QByteArray &data);

  void clear();

protected:
  static QVariant getValue(const QVariantList &valueList, const QString &name);

private:
  QPointer<qbinarizer::ExprMaster> m_xExprMaster;
  QPointer<qbinarizer::ExprMaster> m_yExprMaster;

  QString m_xField;
  QString m_yField;
  QString m_datafield;
  QPointer<qbinarizer::StructDecoder> m_decoder;
  QPointer<QLineSeries> m_series;
  QPointer<QValueAxis> m_axisX;
  QPointer<QValueAxis> m_axisY;
  QList<QVariantList> m_valueList;
};

#endif // STRUCTCHART_H
