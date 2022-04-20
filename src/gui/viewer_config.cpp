#include "viewer_config.hpp"

ViewerConfig::ViewerConfig(QWidget* parent) : QWidget(parent) {
    layout_ = new QVBoxLayout(this);
    this->setLayout(layout_);

    yaw_text_label_ = new QLabel(tr("Yaw"), this);
    yaw_spin_box_ = new QDoubleSpinBox(this);
    yaw_spin_box_->setDecimals(4);
    yaw_spin_box_->setMinimum(-__DBL_MAX__);
    yaw_spin_box_->setMaximum(__DBL_MAX__);
    yaw_spin_box_->setSingleStep(0.01);
    layout_->addWidget(yaw_text_label_);
    layout_->addWidget(yaw_spin_box_);

    pitch_text_label_ = new QLabel(tr("Pitch"), this);
    pitch_spin_box_ = new QDoubleSpinBox(this);
    pitch_spin_box_->setDecimals(4);
    pitch_spin_box_->setMinimum(-__DBL_MAX__);
    pitch_spin_box_->setMaximum(__DBL_MAX__);
    pitch_spin_box_->setSingleStep(0.01);
    layout_->addWidget(pitch_text_label_);
    layout_->addWidget(pitch_spin_box_);

    sensitivity_text_label_ = new QLabel(tr("Sensitivity"), this);
    sensitivity_spin_box_ = new QDoubleSpinBox(this);
    sensitivity_spin_box_->setDecimals(4);
    sensitivity_spin_box_->setMinimum(-__DBL_MAX__);
    sensitivity_spin_box_->setMaximum(__DBL_MAX__);
    sensitivity_spin_box_->setSingleStep(0.01);
    layout_->addWidget(sensitivity_text_label_);
    layout_->addWidget(sensitivity_spin_box_);

    move_speed_text_label_ = new QLabel(tr("Move Speed"), this);
    move_speed_spin_box_ = new QDoubleSpinBox(this);
    move_speed_spin_box_->setDecimals(4);
    move_speed_spin_box_->setMinimum(-__DBL_MAX__);
    move_speed_spin_box_->setMaximum(__DBL_MAX__);
    move_speed_spin_box_->setSingleStep(0.01);
    layout_->addWidget(move_speed_text_label_);
    layout_->addWidget(move_speed_spin_box_);

    cell_size_text_label_ = new QLabel(tr("Cell Size"), this);
    cell_size_spin_box_ = new QDoubleSpinBox(this);
    cell_size_spin_box_->setDecimals(4);
    cell_size_spin_box_->setMinimum(-__DBL_MAX__);
    cell_size_spin_box_->setMaximum(__DBL_MAX__);
    cell_size_spin_box_->setSingleStep(0.5);
    layout_->addWidget(cell_size_text_label_);
    layout_->addWidget(cell_size_spin_box_);

    view_mode_text_label_ = new QLabel(tr("View Mode"), this);
    view_mode_combo_box_ = new QComboBox(this);
    view_mode_combo_box_->addItem(tr("Refresh"), (int)ViewMode::Refresh);
    view_mode_combo_box_->addItem(tr("Accumulate"), (int)ViewMode::Accumulate);
    layout_->addWidget(view_mode_text_label_);
    layout_->addWidget(view_mode_combo_box_);

    layout_->addStretch();

    connect(yaw_spin_box_, &QDoubleSpinBox::valueChanged, this,
            &ViewerConfig::yawChanged);
    connect(pitch_spin_box_, &QDoubleSpinBox::valueChanged, this,
            &ViewerConfig::pitchChanged);
    connect(sensitivity_spin_box_, &QDoubleSpinBox::valueChanged, this,
            &ViewerConfig::sensitivityChanged);
    connect(move_speed_spin_box_, &QDoubleSpinBox::valueChanged, this,
            &ViewerConfig::moveSpeedChanged);
    connect(cell_size_spin_box_, &QDoubleSpinBox::valueChanged, this,
            &ViewerConfig::cellSizeChanged);
    connect(view_mode_combo_box_, &QComboBox::currentIndexChanged, this,
            &ViewerConfig::viewModeHandler);
}

void ViewerConfig::setYaw(const float& yaw) {
    yaw_spin_box_->setValue(yaw);
}
void ViewerConfig::setPitch(const float& pitch) {
    pitch_spin_box_->setValue(pitch);
}
void ViewerConfig::setSensitivity(const float& sensitivity) {
    sensitivity_spin_box_->setValue(sensitivity);
}
void ViewerConfig::setMoveSpeed(const float& move_speed) {
    move_speed_spin_box_->setValue(move_speed);
}
void ViewerConfig::setCellSize(const float& cell_size) {
    cell_size_spin_box_->setValue(cell_size);
}

void ViewerConfig::viewModeHandler(int index) {
    int data = view_mode_combo_box_->itemData(index).toInt();
    emit viewModeChanged((ViewMode)data);
}
