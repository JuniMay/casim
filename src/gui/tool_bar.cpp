#include "tool_bar.hpp"

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent) {
    open_folder_action_ =
        this->addAction(QIcon(":/assets/folder.png"), "Open Folder");
    evolve_step_action_ = this->addAction(QIcon(":/assets/evolve_step.png"),
                                          tr("Evolve by Step"));
    evolve_action_ =
        this->addAction(QIcon(":/assets/evolve.png"), tr("Evolve"));
    stop_action_ = this->addAction(QIcon(":/assets/stop.png"), tr("Stop"));
    reset_action_ = this->addAction(QIcon(":/assets/reset.png"), tr("Reset"));
    random_action_ =
        this->addAction(QIcon(":/assets/random.png"), tr("Random"));
    help_action_ = this->addAction(QIcon(":/assets/help.png"), tr("Help"));

    connect(evolve_action_, &QAction::triggered, this, &ToolBar::evolveHandler);
    connect(evolve_step_action_, &QAction::triggered, this,
            &ToolBar::evolveStepHandler);
    connect(reset_action_, &QAction::triggered, this, &ToolBar::resetHandler);

    connect(open_folder_action_, &QAction::triggered, this,
            &ToolBar::openFolderHandler);
    connect(stop_action_, &QAction::triggered, this, &ToolBar::stopHandler);
    connect(random_action_, &QAction::triggered, this, &ToolBar::randomSignal);
    connect(help_action_, &QAction::triggered, this, &ToolBar::helpHandler);
}

void ToolBar::evolveHandler() {
    emit evolveSignal();
}

void ToolBar::stopHandler() {
    emit stopSignal();
}

void ToolBar::evolveStepHandler() {
    emit evolveStepSignal();
}

void ToolBar::resetHandler() {
    emit resetSignal();
}

void ToolBar::openFolderHandler() {
    emit openFolderSignal();
}

void ToolBar::randomHandler() {
    emit randomSignal();
}

void ToolBar::helpHandler() {
    QPointer<HelpWidget> help_widget_ = new HelpWidget();
    help_widget_->show();
}