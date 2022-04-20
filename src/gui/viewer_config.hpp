#ifndef CASIM_GUI_VIEWER_CONFIG_HPP_
#define CASIM_GUI_VIEWER_CONFIG_HPP_

#include "gui/common.hpp"
#include "gui/viewer.hpp"

class ViewerConfig : public QWidget {
    Q_OBJECT
   public:
    explicit ViewerConfig(QWidget* parent = nullptr);

   signals:
    // xxx_changed means that the corresponding value is changed in spin box.
    void yawChanged(const float& yaw);
    void pitchChanged(const float& pitch);
    void sensitivityChanged(const float& sensitivity);
    void moveSpeedChanged(const float& move_speed);
    void cellSizeChanged(const float& cell_size);

    void viewModeChanged(const ViewMode& view_mode);

   public slots:
    // set_xxx means the corresponding value is changed somewhere else and need
    // to be update here.
    void setYaw(const float& yaw);
    void setPitch(const float& pitch);
    void setSensitivity(const float& sensitivity);
    void setMoveSpeed(const float& move_speed);
    void setCellSize(const float& cell_size);

    void viewModeHandler(int index);

   private:
    QPointer<QLabel> yaw_text_label_;
    QPointer<QDoubleSpinBox> yaw_spin_box_;

    QPointer<QLabel> pitch_text_label_;
    QPointer<QDoubleSpinBox> pitch_spin_box_;

    QPointer<QLabel> sensitivity_text_label_;
    QPointer<QDoubleSpinBox> sensitivity_spin_box_;

    QPointer<QLabel> move_speed_text_label_;
    QPointer<QDoubleSpinBox> move_speed_spin_box_;

    QPointer<QLabel> cell_size_text_label_;
    QPointer<QDoubleSpinBox> cell_size_spin_box_;

    QPointer<QLabel> view_mode_text_label_;
    QPointer<QComboBox> view_mode_combo_box_;

    QPointer<QVBoxLayout> layout_;
};

#endif  // CASIM_GUI_VIEWER_CONFIG_HPP_
