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
    void viewerYawChangedFromViewer(const float& yaw);
    void viewerPitchChangedFromViewer(const float& pitch);
    void viewerSensitivityChangedFromViewer(const float& sensitivity);
    void viewerMoveSpeedChangedFromViewer(const float& move_speed);
    void viewerCellSizeChangedFromViewer(const float& cell_size);

    void patternAdd(const size_t& x,
                    const size_t& y,
                    const size_t& z,
                    const uint32_t& state);
    void patternLoad();
    void patternSave();
    void patternReset();
    void patternResize(const size_t& depth,
                       const size_t& height,
                       const size_t& width);

    // from viewer_config_
    void viewerYawChangedFromConfig(const float& yaw);
    void viewerPitchChangedFromConfig(const float& pitch);
    void viewerSensitivityChangedFromConfig(const float& sensitivity);
    void viewerMoveSpeedChangedFromConfig(const float& move_speed);
    void viewerCellSizeChangedFromConfig(const float& cell_size);
    void viewerViewModeChangedFromConfig(const ViewMode& view_mode);

   private:
    QPointer<QScrollArea> viewer_config_scroll_area_;
    QPointer<QScrollArea> pattern_config_scroll_area_;
    QPointer<PatternConfig> pattern_config_;
    QPointer<ViewerConfig> viewer_config_;
};

#endif
