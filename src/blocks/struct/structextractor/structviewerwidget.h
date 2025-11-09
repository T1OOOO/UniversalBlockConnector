#ifndef STRUCTVIEWERWIDGET_H
#define STRUCTVIEWERWIDGET_H

#include <QElapsedTimer>
#include <QPointer>
#include <QPushButton>
#include <QRadioButton>
#include <QTableView>
#include <QTextEdit>
#include <QWidget>

#include "common/bytearraydatawidget.h"
#include "structviewerlistmodel.h"

class StructViewerWidget : public ByteArrayDataWidget {
  Q_OBJECT
public:
  explicit StructViewerWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

  void onReceiveData(const QByteArray &data) override;

signals:

public slots:

private:
  QPointer<QTextEdit> m_editor;
  QPointer<QTableView> m_table;
  QPointer<StructViewerListModel> m_model;
};

#endif // STRUCTVIEWERWIDGET_H
