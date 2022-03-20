#ifndef CASIM_GUI_RULE_EDITOR_HPP_
#define CASIM_GUI_RULE_EDITOR_HPP_

#include "gui/common.hpp"
#include "gui/viewer_config.hpp"
#include "gui/pattern_config.hpp"

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
  void viewer_cell_size_changed_from_viewer(const float& cell_size);
  // from viewer_config_
  void viewer_yaw_changed_from_config(const float& yaw);
  void viewer_pitch_changed_from_config(const float& pitch);
  void viewer_sensitivity_changed_from_config(const float& sensitivity);
  void viewer_move_speed_changed_from_config(const float& move_speed);
  void viewer_cell_size_changed_from_config(const float& cell_size);

 private:
  QPointer<QWidget> dummy1_, dummy2_;
  QPointer<QScrollArea> viewer_config_scroll_area_;
  QPointer<QScrollArea> pattern_config_scroll_area_;
  QPointer<PatternConfig> pattern_config_;
  QPointer<ViewerConfig> viewer_config_;
};

#endif
