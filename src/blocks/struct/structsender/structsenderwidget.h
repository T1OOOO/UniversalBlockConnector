#ifndef STRUCTSENDERWIDGET_H
#define STRUCTSENDERWIDGET_H

#include <QLineEdit>
#include <QPointer>
#include <QTextEdit>
#include <QTreeView>

#include "../../../3rdparty/QJsonModel/qjsonmodel.h"
#include "common/bytearraydatawidget.h"
#include <qbinarizer/StructEncoder>

class StructSenderWidget : public ByteArrayDataWidget {
  Q_OBJECT
public:
  explicit StructSenderWidget(QWidget *parent = nullptr);

  QJsonObject saveSettings() const override;

  void restoreSettings(const QJsonObject &obj) override;

  void onReceiveData(const QByteArray &data) override;

signals:

public slots:

private:
  QPointer<qbinarizer::StructEncoder> m_encoder;
  QPointer<QTextEdit> m_editor;
  QPointer<QLineEdit> m_data;
  QPointer<QTreeView> m_view;
  QPointer<QJsonModel> m_model;
};

#endif // STRUCTSENDERWIDGET_H
