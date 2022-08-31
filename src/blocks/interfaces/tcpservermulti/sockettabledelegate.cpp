#include "sockettabledelegate.h"
#include <QApplication>
#include <QMouseEvent>

SocketTableDelegate::SocketTableDelegate(QObject *parent)
    : QStyledItemDelegate{parent}, m_pressedRow{-1}, m_mouseOver{false} {}

void SocketTableDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {
  QStyleOptionButton button;
  button.rect = option.rect;
  button.text = "X";

  const int row = index.row();
  button.state = m_pressedRow == row && m_mouseOver
                     ? QStyle::State_Enabled | QStyle::State_Sunken
                     : QStyle::State_Enabled;

  QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

bool SocketTableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) {
  const int row = index.row();

  if (event->type() == QEvent::MouseButtonRelease) {
    QMouseEvent *e = static_cast<QMouseEvent *>(event);
    if (option.rect.contains(e->pos())) {

      emit signal_close(row);
    }

    m_pressedRow = -1;
  } else if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *e = static_cast<QMouseEvent *>(event);

    if (option.rect.contains(e->pos())) {
      m_pressedRow = row;
      m_mouseOver = true;
    }
  } else if (event->type() == QEvent::MouseMove) {
    QMouseEvent *e = static_cast<QMouseEvent *>(event);

    m_mouseOver = option.rect.contains(e->pos());
  }

  return true;
}

// QSize SocketTableDelegate::sizeHint(const QStyleOptionViewItem &option,
//                                     const QModelIndex &index) const {
//   return QSize(10, 10);
// }
