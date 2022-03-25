#include "gui/logger.hpp"

Logger::Logger(QWidget* parent) : QWidget(parent) {
  layout_ = new QHBoxLayout(this);
  this->setLayout(layout_);
  text_edit_ = new QTextEdit;

  text_edit_->setPlainText("");
  layout_->addWidget(text_edit_);

  text_edit_->setReadOnly(true);

  text_edit_->setFont(QFont("Consolas"));
}

void Logger::log(const QString& msg) {
  buffer_ += msg + "\n";
  text_edit_->setPlainText(buffer_);
  text_edit_->verticalScrollBar()->setValue(
      text_edit_->verticalScrollBar()->maximum());
}