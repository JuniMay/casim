#ifndef CASIM_GUI_VIEWER_CONFIG_HPP_
#define CASIM_GUI_VIEWER_CONFIG_HPP_

#include "gui/common.hpp"

class ViewerConfig : public QWidget {
  Q_OBJECT
 public:
  explicit ViewerConfig(QWidget* parent = nullptr);

 signals:
  // xxx_changed means that the corresponding value is changed in spin box.
  void yaw_changed(const float& yaw);
  void pitch_changed(const float& pitch);
  void sensitivity_changed(const float& sensitivity);
  void move_speed_changed(const float& move_speed);

 public slots:
  // set_xxx means the corresponding value is changed somewhere else and need to
  // be update here.
  void set_yaw(const float& yaw);
  void set_pitch(const float& pitch);
  void set_sensitivity(const float& sensitivity);
  void set_move_speed(const float& move_speed);

 private:
  QPointer<QLabel> yaw_text_label_;
  QPointer<QDoubleSpinBox> yaw_spin_box_;

  QPointer<QLabel> pitch_text_label_;
  QPointer<QDoubleSpinBox> pitch_spin_box_;

  QPointer<QLabel> sensitivity_text_label_;
  QPointer<QDoubleSpinBox> sensitivity_spin_box_;

  QPointer<QLabel> move_speed_text_label_;
  QPointer<QDoubleSpinBox> move_speed_spin_box_;

  QPointer<QVBoxLayout> layout_;
};

#endif  // CASIM_GUI_VIEWER_CONFIG_HPP_
