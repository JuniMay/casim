#include "gui/config_editor.hpp"

ConfigEditor::ConfigEditor(QWidget *parent) : QTabWidget(parent) {
  dummy1_ = new QWidget(this);
  dummy2_ = new QWidget(this);
  this->addTab(dummy1_, "Rule");
  this->addTab(dummy2_, "Color");
}
