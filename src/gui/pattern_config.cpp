#include "gui/pattern_config.hpp"

PatternConfig::PatternConfig(QWidget* parent) : QWidget(parent) {
  x_label_ = new QLabel(tr("X"), this);
  x_line_edit_ = new QLineEdit(this);

  y_label_ = new QLabel(tr("Y"), this);
  y_line_edit_ = new QLineEdit(this);

  z_label_ = new QLabel(tr("Z"), this);
  z_line_edit_ = new QLineEdit(this);

  state_label_ = new QLabel(tr("State"), this);
  state_line_edit_ = new QLineEdit(this);

  add_button_ = new QPushButton(tr("Add Cell"), this);
  load_button_ = new QPushButton(tr("Load From File"), this);
  save_button_ = new QPushButton(tr("Save to File"), this);
  reset_button_ = new QPushButton(tr("Reset"), this);

  layout_ = new QGridLayout(this);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 3);

  layout_->addWidget(x_label_, 0, 0, Qt::AlignRight);
  layout_->addWidget(x_line_edit_, 0, 1);
  layout_->addWidget(y_label_, 1, 0, Qt::AlignRight);
  layout_->addWidget(y_line_edit_, 1, 1);
  layout_->addWidget(z_label_, 2, 0, Qt::AlignRight);
  layout_->addWidget(z_line_edit_, 2, 1);
  layout_->addWidget(state_label_, 3, 0, Qt::AlignRight);
  layout_->addWidget(state_line_edit_, 3, 1);
  layout_->addWidget(add_button_, 4, 0, 1, 2);
  layout_->addWidget(load_button_, 5, 0, 1, 2);
  layout_->addWidget(save_button_, 6, 0, 1, 2);
  layout_->addWidget(reset_button_, 7, 0, 1, 2);

  layout_->setAlignment(Qt::AlignTop);

  connect(add_button_, &QPushButton::clicked, this,
          &PatternConfig::add_button_clicked_handler);
  connect(load_button_, &QPushButton::clicked, this,
          &PatternConfig::load_signal);
  connect(save_button_, &QPushButton::clicked, this,
          &PatternConfig::save_signal);
  connect(reset_button_, &QPushButton::clicked, this,
          &PatternConfig::reset_signal);
}

void PatternConfig::add_button_clicked_handler() {
  size_t x = x_line_edit_->text().toULongLong();
  size_t y = y_line_edit_->text().toULongLong();
  size_t z = z_line_edit_->text().toULongLong();
  uint32_t state = state_line_edit_->text().toULongLong();

  emit add_signal(x, y, z, state);
}