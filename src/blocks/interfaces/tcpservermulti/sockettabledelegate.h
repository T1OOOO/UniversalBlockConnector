#ifndef SOCKETTABLEDELEGATE_H
#define SOCKETTABLEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class SocketTableDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit SocketTableDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) override;

  //  QSize sizeHint(const QStyleOptionViewItem &option,
  //                 const QModelIndex &index) const override;

signals:
  void signal_close(const int row);

private:
  bool m_mouseOver;
  int m_pressedRow;
};

#endif // SOCKETTABLEDELEGATE_H
