#include "gui/logger.hpp"

Logger::Logger(QWidget *parent) : QWidget(parent) {
  layout_ = new QHBoxLayout(this);
  this->setLayout(layout_);
  text_edit_ = new QTextEdit;
  layout_->addWidget(text_edit_);

  text_edit_->setReadOnly(true);
}
