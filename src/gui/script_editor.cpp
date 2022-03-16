#include "gui/script_editor.hpp"

ScriptHighlighter::ScriptHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
  HighlightingRule rule;
  keyword_format_.setForeground(Qt::darkBlue);
  keyword_format_.setFontWeight(QFont::Bold);

  const QString keyword_regex_rules[] = {
      QStringLiteral("\\bfunction\\b"), QStringLiteral("\\bend\\b"),
      QStringLiteral("\\bif\\b"),       QStringLiteral("\\bthen\\b"),
      QStringLiteral("\\belse\\b"),     QStringLiteral("\\bfor\\b"),
      QStringLiteral("\\band\\b"),      QStringLiteral("\\bbreak\\b"),
      QStringLiteral("\\bdo\\b"),       QStringLiteral("\\belseif\\b"),
      QStringLiteral("\\bfalse\\b"),    QStringLiteral("\\bin\\b"),
      QStringLiteral("\\blocal\\b"),    QStringLiteral("\\bnil\\b"),
      QStringLiteral("\\bor\\b"),       QStringLiteral("\\brepeat\\b"),
      QStringLiteral("\\breturn\\b"),   QStringLiteral("\\btrue\\b"),
      QStringLiteral("\\buntil\\b"),    QStringLiteral("\\bwhile\\b"),
  };
  for (const QString &regex_rule : keyword_regex_rules) {
    rule.regex_rule = QRegularExpression(regex_rule);
    rule.format = keyword_format_;
    highting_rules_.append(rule);
  }

  function_format_.setFontItalic(true);
  function_format_.setForeground(Qt::blue);
  rule.regex_rule = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
  rule.format = function_format_;
  highting_rules_.append(rule);
}

void ScriptHighlighter::highlightBlock(const QString &text) {
  
}