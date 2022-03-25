#ifndef CASIM_GUI_LOGGER_HPP_
#define CASIM_GUI_LOGGER_HPP_

#include "gui/common.hpp"

class Logger : public QWidget {
  Q_OBJECT
 public:
  explicit Logger(QWidget* parent = nullptr);

  void log(const QString& msg);

 private:
  QPointer<QHBoxLayout> layout_;
  QPointer<QTextEdit> text_edit_;

  QPointer<QTextDocument> document_;
  QString buffer_;
};

#endif
