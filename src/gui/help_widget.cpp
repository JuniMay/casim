#include "gui/help_widget.hpp"

HelpWidget::HelpWidget(QWidget* parent) : QWidget(parent) {
  this->setWindowTitle(tr("Help"));
  layout_ = new QVBoxLayout(this);
  xtensor_button_ = new QPushButton(tr("About xtensor"), this);
  xtl_button_ = new QPushButton(tr("About xtl"), this);
  lua_button_ = new QPushButton(tr("About Lua"), this);
  casim_button_ = new QPushButton(tr("About Casim"), this);
  qt_button_ = new QPushButton(tr("About Qt"), this);
  freeglut_button_ = new QPushButton(tr("About FreeGLUT"), this);

  this->setMinimumSize(200, 150);

  layout_->addWidget(casim_button_);
  layout_->addWidget(freeglut_button_);
  layout_->addWidget(lua_button_);
  layout_->addWidget(qt_button_);
  layout_->addWidget(xtl_button_);
  layout_->addWidget(xtensor_button_);
  layout_->addStretch();

  connect(casim_button_, &QPushButton::clicked, this,
          &HelpWidget::casim_handler);
  connect(xtensor_button_, &QPushButton::clicked, this,
          &HelpWidget::xtensor_handler);
  connect(xtl_button_, &QPushButton::clicked, this, &HelpWidget::xtl_handler);
  connect(lua_button_, &QPushButton::clicked, this, &HelpWidget::lua_handler);
  connect(qt_button_, &QPushButton::clicked, this, &HelpWidget::qt_handler);
  connect(freeglut_button_, &QPushButton::clicked, this,
          &HelpWidget::freeglut_handler);
}

void HelpWidget::xtensor_handler() {
  QFile license(":/third_party/xtensor/LICENSE");
  license.open(QIODevice::ReadOnly);
  QMessageBox::about(this, "About xtensor", license.readAll());
}

void HelpWidget::xtl_handler() {
  QFile license(":/third_party/xtl/LICENSE");
  license.open(QIODevice::ReadOnly);
  QMessageBox::about(this, "About xtl", license.readAll());
}

void HelpWidget::casim_handler() {
  QFile license(":/LICENSE");
  license.open(QIODevice::ReadOnly);
  QMessageBox::about(this, "About Casim", license.readAll());
}

void HelpWidget::lua_handler() {
  QFile license(":/third_party/lua/LICENSE");
  license.open(QIODevice::ReadOnly);
  QMessageBox::about(this, "About Lua", license.readAll());
}

void HelpWidget::qt_handler() {
  QMessageBox::aboutQt(this, tr("About Qt"));
}

void HelpWidget::freeglut_handler() {
  QFile license(":/third_party/freeglut/COPYING");
  license.open(QIODevice::ReadOnly);
  QMessageBox::about(this, "About FreeGLUT", license.readAll());
}
