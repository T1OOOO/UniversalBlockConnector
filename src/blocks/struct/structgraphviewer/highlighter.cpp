#include "highlighter.h"
#include <QDebug>

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
  HighlightingRule rule;

  rule.pattern = QRegularExpression("(\"[^\"]*\")");
  rule.format.setForeground(Qt::darkBlue);
  rule.format.setFontWeight(QFont::Bold);
  rules.append(rule);

  rule.pattern = QRegularExpression(":+(?:[: []*)(\"[^\"]*\")");
  rule.format.setForeground(Qt::darkCyan);
  rule.format.setFontWeight(QFont::Normal);
  rules.append(rule);

  rule.pattern = QRegularExpression("\\,(?:[ ]*)\"([^\"]*)\"(?:\\s*)");
  rule.format.setForeground(Qt::darkCyan);
  rules.append(rule);

  rule.pattern = QRegularExpression("([0-9.]+)(?!.*\")");
  rule.format.setForeground(Qt::darkGreen);
  rules.append(rule);
}

void Highlighter::highlightBlock(const QString &text) {
  // object
  foreach (const HighlightingRule &rule, rules) {
    const QRegularExpression &expression = rule.pattern;
    QRegularExpressionMatchIterator matchIt = expression.globalMatch(text);
    while (matchIt.hasNext()) {
      const QRegularExpressionMatch match = matchIt.next();
      int index = match.capturedStart(1);
      int length = match.capturedLength(1);
      setFormat(index, length, rule.format);
    }
  }
}
