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
            &HelpWidget::casimHandler);
    connect(xtensor_button_, &QPushButton::clicked, this,
            &HelpWidget::xtensorHandler);
    connect(xtl_button_, &QPushButton::clicked, this, &HelpWidget::xtlHandler);
    connect(lua_button_, &QPushButton::clicked, this, &HelpWidget::luaHandler);
    connect(qt_button_, &QPushButton::clicked, this, &HelpWidget::qtHandler);
    connect(freeglut_button_, &QPushButton::clicked, this,
            &HelpWidget::freeglutHandler);
}

void HelpWidget::xtensorHandler() {
    QFile license(":/third_party/xtensor/LICENSE");
    license.open(QIODevice::ReadOnly);
    QMessageBox::about(this, "About xtensor", license.readAll());
}

void HelpWidget::xtlHandler() {
    QFile license(":/third_party/xtl/LICENSE");
    license.open(QIODevice::ReadOnly);
    QMessageBox::about(this, "About xtl", license.readAll());
}

void HelpWidget::casimHandler() {
    QFile license(":/LICENSE");
    license.open(QIODevice::ReadOnly);
    QMessageBox::about(this, "About Casim", license.readAll());
}

void HelpWidget::luaHandler() {
    QFile license(":/third_party/lua/LICENSE");
    license.open(QIODevice::ReadOnly);
    QMessageBox::about(this, "About Lua", license.readAll());
}

void HelpWidget::qtHandler() {
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void HelpWidget::freeglutHandler() {
    QFile license(":/third_party/freeglut/COPYING");
    license.open(QIODevice::ReadOnly);
    QMessageBox::about(this, "About FreeGLUT", license.readAll());
}
