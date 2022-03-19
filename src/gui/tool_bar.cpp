#include "tool_bar.hpp"

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
  file_action_ = this->addAction(QIcon(":/assets/file.png"), "File");
  evolve_action_ = this->addAction(QIcon(":/assets/evolve.png"), "Evolve");
  evolve_step_action_ =
      this->addAction(QIcon(":/assets/evolve_step.png"), "Evolve by Step");
  stop_action_ = this->addAction(QIcon(":/assets/stop.png"), "Stop");
  reset_action_ = this->addAction(QIcon(":/assets/reset.png"), "reset");

  connect(evolve_action_, &QAction::triggered, this,
          &ToolBar::evolve_action_triggered_handler);
  connect(reset_action_, &QAction::triggered, this,
          &ToolBar::reset_action_triggered_handler);
}

void ToolBar::evolve_action_triggered_handler() { emit evolve_signal(); }
void ToolBar::reset_action_triggered_handler() { emit reset_signal(); }
