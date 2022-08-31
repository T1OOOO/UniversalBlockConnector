#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QTimer>
#include <QWidget>

class LedWidget : public QWidget {
  Q_OBJECT
public:
  explicit LedWidget(QWidget *parent = nullptr);

  void setOn(const bool value);
  void switchOnTimer();

protected:
  void paintEvent(QPaintEvent *e) override;

public slots:
  void slot_onTimer();

private:
  bool m_on;
  int m_timeout;
  QTimer m_timer;
};

#endif // LEDWIDGET_H
