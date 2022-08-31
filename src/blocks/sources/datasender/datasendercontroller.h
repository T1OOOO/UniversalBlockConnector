#ifndef DATASENDERCONTROLLER_H
#define DATASENDERCONTROLLER_H

#include <QObject>

#include "../../common/bytearraydatacontroller.h"
#include "datasenderwidget.h"

class DataSenderController : public ByteArrayDataController {
  Q_OBJECT
public:
  explicit DataSenderController();

signals:

private:
  QPointer<DataSenderWidget> m_widget;
};

#endif // DATASENDERCONTROLLER_H
