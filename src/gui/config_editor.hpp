#ifndef CASIM_GUI_RULE_EDITOR_HPP_
#define CASIM_GUI_RULE_EDITOR_HPP_

#include "gui/common.hpp"
#include "gui/viewer_config.hpp"

class ConfigEditor : public QTabWidget {
  Q_OBJECT
 public:
  explicit ConfigEditor(QWidget* parent = nullptr);

 signals:
  // from viewer_
  void viewer_yaw_changed_from_viewer(const float& yaw);
  void viewer_pitch_changed_from_viewer(const float& pitch);
  void viewer_sensitivity_changed_from_viewer(const float& sensitivity);
  void viewer_move_speed_changed_from_viewer(const float& move_speed);
  // from viewer_config_
  void viewer_yaw_changed_from_config(const float& yaw);
  void viewer_pitch_changed_from_config(const float& pitch);
  void viewer_sensitivity_changed_from_config(const float& sensitivity);
  void viewer_move_speed_changed_from_config(const float& move_speed);

 private:
  QPointer<QWidget> dummy1_, dummy2_;
  QPointer<QScrollArea> viewer_config_scroll_area_;
  QPointer<ViewerConfig> viewer_config_;
};

#endif
