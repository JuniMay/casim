#include "gui/config_editor.hpp"

ConfigEditor::ConfigEditor(QWidget* parent) : QTabWidget(parent) {
    viewer_config_scroll_area_ = new QScrollArea(this);
    viewer_config_ = new ViewerConfig(viewer_config_scroll_area_);
    viewer_config_scroll_area_->setWidget(viewer_config_);
    viewer_config_scroll_area_->setWidgetResizable(true);
    this->addTab(viewer_config_scroll_area_, tr("Viewer"));

    pattern_config_scroll_area_ = new QScrollArea(this);
    pattern_config_ = new PatternConfig(pattern_config_scroll_area_);
    pattern_config_scroll_area_->setWidget(pattern_config_);
    pattern_config_scroll_area_->setWidgetResizable(true);
    this->addTab(pattern_config_scroll_area_, tr("Pattern"));

    // The ConfigEditor is basicly a intermeidate for signals
    // Qt's signals and slots are reallu annoying.
    // If anyone knows a better solution please let me know.
    connect(this, &ConfigEditor::viewerYawChangedFromViewer, viewer_config_,
            &ViewerConfig::setYaw);
    connect(this, &ConfigEditor::viewerPitchChangedFromViewer, viewer_config_,
            &ViewerConfig::setPitch);
    connect(this, &ConfigEditor::viewerSensitivityChangedFromViewer,
            viewer_config_, &ViewerConfig::setSensitivity);
    connect(this, &ConfigEditor::viewerMoveSpeedChangedFromViewer,
            viewer_config_, &ViewerConfig::setMoveSpeed);
    connect(this, &ConfigEditor::viewerCellSizeChangedFromViewer,
            viewer_config_, &ViewerConfig::setCellSize);

    connect(viewer_config_, &ViewerConfig::yawChanged, this,
            &ConfigEditor::viewerYawChangedFromConfig);
    connect(viewer_config_, &ViewerConfig::pitchChanged, this,
            &ConfigEditor::viewerPitchChangedFromConfig);
    connect(viewer_config_, &ViewerConfig::sensitivityChanged, this,
            &ConfigEditor::viewerSensitivityChangedFromConfig);
    connect(viewer_config_, &ViewerConfig::moveSpeedChanged, this,
            &ConfigEditor::viewerMoveSpeedChangedFromConfig);
    connect(viewer_config_, &ViewerConfig::cellSizeChanged, this,
            &ConfigEditor::viewerCellSizeChangedFromConfig);
    connect(viewer_config_, &ViewerConfig::viewModeChanged, this,
            &ConfigEditor::viewerViewModeChangedFromConfig);

    connect(pattern_config_, &PatternConfig::addSignal, this,
            &ConfigEditor::patternAdd);
    connect(pattern_config_, &PatternConfig::loadSignal, this,
            &ConfigEditor::patternLoad);
    connect(pattern_config_, &PatternConfig::saveSignal, this,
            &ConfigEditor::patternSave);
    connect(pattern_config_, &PatternConfig::resetSignal, this,
            &ConfigEditor::patternReset);
    connect(pattern_config_, &PatternConfig::resizeSignal, this,
            &ConfigEditor::patternResize);
}
