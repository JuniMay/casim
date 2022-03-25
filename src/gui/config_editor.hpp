#ifndef CASIM_GUI_RULE_EDITOR_HPP_
#define CASIM_GUI_RULE_EDITOR_HPP_

#include "gui/common.hpp"
#include "gui/pattern_config.hpp"
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
  void viewer_cell_size_changed_from_viewer(const float& cell_size);

  void pattern_add(const size_t& x,
                   const size_t& y,
                   const size_t& z,
                   const uint32_t& state);
  void pattern_load();
  void pattern_save();
  void pattern_reset();
  void pattern_resize(const size_t& depth,
                      const size_t& height,
                      const size_t& width);

  // from viewer_config_
  void viewer_yaw_changed_from_config(const float& yaw);
  void viewer_pitch_changed_from_config(const float& pitch);
  void viewer_sensitivity_changed_from_config(const float& sensitivity);
  void viewer_move_speed_changed_from_config(const float& move_speed);
  void viewer_cell_size_changed_from_config(const float& cell_size);
  void viewer_view_mode_changed_from_config(const ViewMode& view_mode);

 private:
  QPointer<QScrollArea> viewer_config_scroll_area_;
  QPointer<QScrollArea> pattern_config_scroll_area_;
  QPointer<PatternConfig> pattern_config_;
  QPointer<ViewerConfig> viewer_config_;
};

#endif
