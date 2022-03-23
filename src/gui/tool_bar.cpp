#include "tool_bar.hpp"

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent) {
  folder_action_ = this->addAction(QIcon(":/assets/folder.png"), "Open Folder");
  evolve_step_action_ =
      this->addAction(QIcon(":/assets/evolve_step.png"), "Evolve by Step");
  evolve_action_ = this->addAction(QIcon(":/assets/evolve.png"), "Evolve");
  stop_action_ = this->addAction(QIcon(":/assets/stop.png"), "Stop");
  reset_action_ = this->addAction(QIcon(":/assets/reset.png"), "reset");

  connect(evolve_action_, &QAction::triggered, this,
          &ToolBar::evolve_action_triggered_handler);
  connect(evolve_step_action_, &QAction::triggered, this,
          &ToolBar::evolve_step_action_triggered_handler);
  connect(reset_action_, &QAction::triggered, this,
          &ToolBar::reset_action_triggered_handler);

  connect(folder_action_, &QAction::triggered, this,
          &ToolBar::open_folder_triggered_handler);
  connect(stop_action_, &QAction::triggered, this,
          &ToolBar::stop_action_triggered_handler);
}

void ToolBar::evolve_action_triggered_handler() {
  emit evolve_signal();
}

void ToolBar::stop_action_triggered_handler() {
  emit stop_signal();
}

void ToolBar::evolve_step_action_triggered_handler() {
  emit evolve_step_signal();
}

void ToolBar::reset_action_triggered_handler() {
  emit reset_signal();
}

void ToolBar::open_folder_triggered_handler() {
  emit open_folder();
}
