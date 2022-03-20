#include "gui/config_editor.hpp"

ConfigEditor::ConfigEditor(QWidget* parent) : QTabWidget(parent) {
  viewer_config_scroll_area_ = new QScrollArea(this);
  viewer_config_ = new ViewerConfig(viewer_config_scroll_area_);
  viewer_config_scroll_area_->setWidget(viewer_config_);
  viewer_config_scroll_area_->setWidgetResizable(true);
  this->addTab(viewer_config_scroll_area_, "Viewer");

  pattern_config_scroll_area_ = new QScrollArea(this);
  pattern_config_ = new PatternConfig(pattern_config_scroll_area_);
  pattern_config_scroll_area_->setWidget(pattern_config_);
  pattern_config_scroll_area_->setWidgetResizable(true);
  this->addTab(pattern_config_scroll_area_, "pattern");

  dummy1_ = new QWidget(this);
  dummy2_ = new QWidget(this);
  this->addTab(dummy1_, "Rule");
  this->addTab(dummy2_, "Color");

  // The ConfigEditor is basicly a intermeidate for signals
  // Qt's signals and slots are reallu annoying.
  // If anyone knows a better solution please let me know.
  connect(this, &ConfigEditor::viewer_yaw_changed_from_viewer, viewer_config_,
          &ViewerConfig::set_yaw);
  connect(this, &ConfigEditor::viewer_pitch_changed_from_viewer, viewer_config_,
          &ViewerConfig::set_pitch);
  connect(this, &ConfigEditor::viewer_sensitivity_changed_from_viewer,
          viewer_config_, &ViewerConfig::set_sensitivity);
  connect(this, &ConfigEditor::viewer_move_speed_changed_from_viewer,
          viewer_config_, &ViewerConfig::set_move_speed);
  connect(this, &ConfigEditor::viewer_cell_size_changed_from_viewer,
          viewer_config_, &ViewerConfig::set_cell_size);

  connect(viewer_config_, &ViewerConfig::yaw_changed, this,
          &ConfigEditor::viewer_yaw_changed_from_config);
  connect(viewer_config_, &ViewerConfig::pitch_changed, this,
          &ConfigEditor::viewer_pitch_changed_from_config);
  connect(viewer_config_, &ViewerConfig::sensitivity_changed, this,
          &ConfigEditor::viewer_sensitivity_changed_from_config);
  connect(viewer_config_, &ViewerConfig::move_speed_changed, this,
          &ConfigEditor::viewer_move_speed_changed_from_config);
  connect(viewer_config_, &ViewerConfig::cell_size_changed, this,
          &ConfigEditor::viewer_cell_size_changed_from_config);
}
