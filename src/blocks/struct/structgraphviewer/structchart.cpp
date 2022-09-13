#include "structchart.h"

#include <QtMath>

StructChart::StructChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart{parent, wFlags} {
  m_decoder = new qbinarizer::StructDecoder(this);

  m_series = new QLineSeries(this);
  addSeries(m_series);

  m_axisX = new QValueAxis();
  addAxis(m_axisX, Qt::AlignBottom);
  m_series->attachAxis(m_axisX);

  m_axisY = new QValueAxis();
  addAxis(m_axisY, Qt::AlignLeft);
  m_series->attachAxis(m_axisY);

  m_xExprMaster = new qbinarizer::ExprMaster(this);
  m_yExprMaster = new qbinarizer::ExprMaster(this);

  legend()->hide();
}

void StructChart::setXField(const QString &name) {
  m_xField = name;
  m_xExprMaster->setExpr(name);

  m_series->clear();
}

void StructChart::setYField(const QString &name) {
  m_yField = name;
  m_yExprMaster->setExpr(name);

  m_series->clear();
}

void StructChart::setDatafield(const QString &datafield) {
  m_datafield = datafield;

  m_series->clear();
}

void StructChart::addData(const QByteArray &data) {
  const QVariantList valueList = m_decoder->decode(m_datafield, data);
  const QVariantList extractedValueList =
      qbinarizer::StructDecoder::extractValues(valueList);

  if (m_yField.isEmpty()) {
    return;
  }

  m_yExprMaster->setVars(extractedValueList);
  const qreal y = m_yExprMaster->eval();

  qreal x = m_series->count() + 1;
  if (!m_xField.isEmpty()) {
    m_xExprMaster->setVars(extractedValueList);
    x = m_xExprMaster->eval();
  }

  if (x > m_axisX->max()) {
    m_axisX->setMax(x);
  } else if (x < m_axisX->min()) {
    m_axisX->setMin(x);
  }

  if (y > m_axisY->max()) {
    m_axisY->setMax(y);
  } else if (y < m_axisY->min()) {
    m_axisY->setMin(y);
  }

  m_series->append(x, y);
  update();
}

void StructChart::clear() {
  m_series->clear();
  m_axisX->setRange(0, 0);
  m_axisY->setRange(0, 0);
  m_xExprMaster->clear();
  m_yExprMaster->clear();
}

QVariant StructChart::getValue(const QVariantList &valueList,
                               const QString &name) {
  if (name.isEmpty()) {
    return {};
  }

  const QVariantList extractedValueList =
      qbinarizer::StructDecoder::extractValues(valueList);

  const auto it =
      std::find_if(extractedValueList.constBegin(),
                   extractedValueList.constEnd(), [&name](const auto &value) {
                     if (value.type() != QVariant::Map) {
                       return false;
                     }

                     const QVariantMap valueMap = value.toMap();
                     if (valueMap.isEmpty()) {
                       return false;
                     }

                     const QString &firstKey = valueMap.firstKey();

                     return name == firstKey;
                   });
  if (it == extractedValueList.constEnd()) {
    return {};
  }

  const QVariant &value = *it;
  if (value.type() != QVariant::Map) {
    return {};
  }

  const QVariantMap valueMap = value.toMap();
  if (valueMap.isEmpty()) {
    return 0.0;
  }

  const QString &firstKey = valueMap.firstKey();
  QVariant valueRes = valueMap[firstKey];

  return valueRes;
}
