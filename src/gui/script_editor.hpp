#ifndef CASIM_GUI_SCRIPT_EDITOR_HPP_
#define CASIM_GUI_SCRIPT_EDITOR_HPP_

#include "gui/common.hpp"

class ScriptHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
 public:
  explicit ScriptHighlighter(QTextDocument *parent = nullptr);

 protected:
  void highlightBlock(const QString &text) override;

 private:
  struct HighlightingRule {
    QRegularExpression regex_rule;
    QTextCharFormat format;
  };
  QVector<HighlightingRule> highting_rules_;

  QTextCharFormat keyword_format_;
  QTextCharFormat function_format_;
  QTextCharFormat string_format_;
  QTextCharFormat number_format_;

  // TODO: comments
};

class ScriptEditor : public QWidget {
  Q_OBJECT
 public:
  explicit ScriptEditor(QWidget *parent = nullptr);

 private:
  QPointer<QTextEdit> editor_;
  QPointer<ScriptHighlighter> script_highlighter_;
  QPointer<QHBoxLayout> layout_;
};

#endif
