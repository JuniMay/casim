#ifndef CASIM_GUI_RULE_EDITOR_HPP_
#define CASIM_GUI_RULE_EDITOR_HPP_

#include "gui/common.hpp"
#include "gui/viewer_config.hpp"

class ConfigEditor : public QTabWidget {
  Q_OBJECT
 public:
  explicit ConfigEditor(QWidget* parent = nullptr);

 signals:
  // xxx_change means the value is changed somewhere else and need to be
  // synchronized
  void viewer_yaw_changed(const float& yaw);
  void viewer_pitch_changed(const float& pitch);
  void viewer_sensitivity_changed(const float& sensitivity);
  void viewer_move_speed_changed(const float& move_speed);
  // xxx_set means th corresponding value is set in the config widget
  // and need to be applied.
  void viewer_yaw_set(const float& yaw);
  void viewer_pitch_set(const float& pitch);
  void viewer_sensitivity_set(const float& sensitivity);
  void viewer_move_speed_set(const float& move_speed);

 private:
  QPointer<QWidget> dummy1_, dummy2_;
  QPointer<QScrollArea> viewer_config_scroll_area_;
  QPointer<ViewerConfig> viewer_config_;
};

#endif
