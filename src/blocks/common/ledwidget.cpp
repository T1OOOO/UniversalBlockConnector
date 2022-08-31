#include "ledwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QtDebug>

namespace {
const QColor defaultColorOn = Qt::green;
const QColor defaultColorOff = Qt::red;
const int defaultTimeot = 500;
} // namespace

LedWidget::LedWidget(QWidget *parent)
    : QWidget{parent}, m_on(false), m_timeout(defaultTimeot) {
  setMinimumSize(10, 10);
  setContentsMargins(0, 0, 0, 0);

  connect(&m_timer, &QTimer::timeout, this, &LedWidget::slot_onTimer);
}

void LedWidget::setOn(const bool value) {
  m_on = value;
  update();
}

void LedWidget::switchOnTimer() {
  if (m_timer.isActive()) {
    m_timer.stop();
  }

  m_timer.start(m_timeout);
  setOn(true);
}

void LedWidget::paintEvent(QPaintEvent *e) {
  QPainter painter(this);
  QPainterPath path;
  path.addEllipse(QRect(QPoint(), size()));
  painter.fillPath(path, m_on ? defaultColorOn : defaultColorOff);
}

void LedWidget::slot_onTimer() {
  m_on = false;
  update();
}
