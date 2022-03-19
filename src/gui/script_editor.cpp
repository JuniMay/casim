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
  rule.regex_rule =
      QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
  rule.format = function_format_;
  highting_rules_.append(rule);

  string_format_.setForeground(Qt::darkYellow);
  rule.regex_rule =
      QRegularExpression(QStringLiteral("\".*\""));
  rule.format = string_format_;
  highting_rules_.append(rule);

  number_format_.setForeground(Qt::darkMagenta);
  rule.regex_rule =
      QRegularExpression(QStringLiteral("\\b[0-9]+\\b"));
  rule.format = number_format_;
  highting_rules_.append(rule);
}

void ScriptHighlighter::highlightBlock(const QString &text) {
  for (const HighlightingRule &rule : qAsConst(highting_rules_)) {
    QRegularExpressionMatchIterator match_iter =
        rule.regex_rule.globalMatch(text);
    while (match_iter.hasNext()) {
      QRegularExpressionMatch match = match_iter.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }
}

ScriptEditor::ScriptEditor(QWidget *parent): QWidget(parent) {
  QFont font;
  font.setFamily("Consolas");
  font.setFixedPitch(true);
  font.setPointSize(12);
  layout_ = new QHBoxLayout(this);

  editor_ = new QTextEdit;
  editor_->setAcceptRichText(false);
  editor_->setFont(font);

  QFontMetrics metrics(font);

  editor_->setTabStopDistance(4 * metrics.horizontalAdvance(' '));
  editor_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  editor_->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);

  script_highlighter_ = new ScriptHighlighter(editor_->document());

  this->setLayout(layout_);

  layout_->addWidget(editor_);

  
}