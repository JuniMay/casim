#ifndef CASIM_GUI_SCRIPT_EDITOR_H_
#define CASIM_GUI_SCRIPT_EDITOR_H_

#include "gui/common.hpp"

class ScriptHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
 public:
  ScriptHighlighter(QTextDocument *parent = nullptr);

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
};

#endif
