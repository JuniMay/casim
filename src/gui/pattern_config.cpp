#include "gui/pattern_config.hpp"

PatternConfig::PatternConfig(QWidget* parent) : QWidget(parent) {
  x_label_ = new QLabel("X", this);
  x_line_edit_ = new QLineEdit(this);

  y_label_ = new QLabel("Y", this);
  y_line_edit_ = new QLineEdit(this);

  z_label_ = new QLabel("Z", this);
  z_line_edit_ = new QLineEdit(this);

  state_label_ = new QLabel("State", this);
  state_line_edit_ = new QLineEdit(this);

  add_button_ = new QPushButton("Add Cell", this);

  layout_ = new QGridLayout(this);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 2);

  layout_->addWidget(x_label_, 0, 0, Qt::AlignRight);
  layout_->addWidget(x_line_edit_, 0, 1);
  layout_->addWidget(y_label_, 1, 0, Qt::AlignRight);
  layout_->addWidget(y_line_edit_, 1, 1);
  layout_->addWidget(z_label_, 2, 0, Qt::AlignRight);
  layout_->addWidget(z_line_edit_, 2, 1);
  layout_->addWidget(state_label_, 3, 0, Qt::AlignRight);
  layout_->addWidget(state_line_edit_, 3, 1);
  layout_->addWidget(add_button_, 4, 0, 1, 2);

  layout_->setAlignment(Qt::AlignTop);
}