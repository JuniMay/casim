#ifndef CASIM_GUI_TOOL_BAR_HPP_
#define CASIM_GUI_TOOL_BAR_HPP_

#include "gui/common.hpp"

#include "help_widget.hpp"

class ToolBar : public QToolBar {
    Q_OBJECT
   public:
    ToolBar(QWidget* parent = nullptr);

   signals:
    void evolveSignal();
    void stopSignal();
    void evolveStepSignal();
    void resetSignal();
    void openFolderSignal();
    void randomSignal();

   public slots:
    void evolveHandler();
    void stopHandler();
    void evolveStepHandler();
    void resetHandler();
    void openFolderHandler();
    void randomHandler();

    void helpHandler();

   private:
    QPointer<QAction> evolve_action_;
    QPointer<QAction> evolve_step_action_;
    QPointer<QAction> stop_action_;
    QPointer<QAction> open_folder_action_;
    QPointer<QAction> reset_action_;
    QPointer<QAction> random_action_;
    QPointer<QAction> help_action_;
};

#endif  // CASIM_GUI_TOOL_BAR_HPP_
