#include "dataviewerwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QScrollBar>

#define TEXT_TIMEOUT 5000
#define TEXT_MAX_SIZE (1024 * 1024 * 1024)

DataViewerWidget::DataViewerWidget(QWidget *parent)
    : ByteArrayDataWidget{parent} {
  auto *widget = new QWidget(this);
  setWidget(widget);

  auto *layout = new QGridLayout(widget);

  QGroupBox *mode = new QGroupBox(tr("Mode"), this);
  mode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  QHBoxLayout *modeLayout = new QHBoxLayout(mode);
  mode->setLayout(modeLayout);

  m_hexMode = new QRadioButton(tr("Hex"), mode);
  m_hexMode->setChecked(true);
  modeLayout->addWidget(m_hexMode);

  m_stringMode = new QRadioButton(tr("String"), mode);
  modeLayout->addWidget(m_stringMode);

  layout->addWidget(mode, 0, 0, 1, 2);

  m_pauseButton = new QPushButton(tr("Pause"), this);
  m_pauseButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  m_pauseButton->setCheckable(true);
  layout->addWidget(m_pauseButton, 1, 0);

  m_clearButton = new QPushButton(tr("Clear"), this);
  m_clearButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(m_clearButton, &QPushButton::clicked,
          [this](bool) { m_view->clear(); });
  layout->addWidget(m_clearButton, 1, 1);

  m_view = new QPlainTextEdit(this);
  m_view->setReadOnly(true);
  m_view->setTextInteractionFlags(Qt::TextSelectableByMouse);
  layout->addWidget(m_view, 2, 0, 1, 2);

  m_timer.start();
}

QJsonObject DataViewerWidget::saveSettings() const {
  QJsonObject obj;
  return obj;
}

void DataViewerWidget::restoreSettings(const QJsonObject &obj) {}

QString toHexString0x(const QByteArray &data) {
  const unsigned char *buf =
      reinterpret_cast<const unsigned char *>(data.constData());
  int buffsize = data.size();

  QString result;
  for (int i = 0; i < buffsize; i++) {
    result += "0x" + QString("%1 ").arg(buf[i], 2, 16, QChar('0')).toUpper();
  }
  result.chop(1);

  return result;
}

QString toStringEscape(const QByteArray &data) {
  QString res;
  res.reserve(data.size() * 1.1);

  for (int i = 0; i < data.size(); i++) {
    const char c = data[i];

    switch (c) {
    case 0x00:
      res += "\\0";
      break;
    case 0x07:
      res += "\\a";
      break;
    case 0x08:
      res += "\\b";
      break;
    case 0x0c:
      res += "\\f";
      break;
    case 0x0a:
      res += "\\n";
      break;
    case 0x0d:
      res += "\\r";
      break;
    case 0x09:
      res += "\\t";
      break;
    case 0x0b:
      res += "\\v";
      break;
    default:
      res += c;
      break;
    }
  }

  return res;
}

void DataViewerWidget::addData(const QByteArray &data) {
  if (m_pauseButton->isChecked()) {
    return;
  }

  QDateTime dateTime = QDateTime::currentDateTime();

  QString dataStr;
  if (m_hexMode->isChecked()) {
    dataStr = toHexString0x(data);
  } else if (m_stringMode->isChecked()) {
    dataStr = toStringEscape(data);
  }

  QString str = dateTime.toString("hh:mm:ss:zzz (%1): %2\n")
                    .arg(data.size())
                    .arg(dataStr);

  QTextCursor cursor = m_view->textCursor();
  cursor.movePosition(QTextCursor::End);
  m_view->setTextCursor(cursor);
  m_view->insertPlainText(str);
  m_view->verticalScrollBar()->setValue(m_view->verticalScrollBar()->maximum());

  if (m_timer.hasExpired(TEXT_TIMEOUT)) {
    QString text = m_view->toPlainText();
    if (text.size() > TEXT_MAX_SIZE) {
      int startPos = text.size() - TEXT_MAX_SIZE + TEXT_MAX_SIZE * 0.2;
      text = text.mid(startPos);

      m_view->setPlainText(text);
    }

    m_timer.restart();
  }
}
