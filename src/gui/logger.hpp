#ifndef CASIM_GUI_LOGGER_HPP_
#define CASIM_GUI_LOGGER_HPP_

#include "gui/common.hpp"

class Logger : public QWidget {
  Q_OBJECT
 public:
  explicit Logger(QWidget* parent = nullptr);

 private:
  QPointer<QHBoxLayout> layout_;
  QPointer<QTextEdit> text_edit_;
};

#endif
