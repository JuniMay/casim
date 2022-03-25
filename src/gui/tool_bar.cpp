#include "tool_bar.hpp"

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent) {
  open_folder_action_ =
      this->addAction(QIcon(":/assets/folder.png"), "Open Folder");
  evolve_step_action_ =
      this->addAction(QIcon(":/assets/evolve_step.png"), tr("Evolve by Step"));
  evolve_action_ = this->addAction(QIcon(":/assets/evolve.png"), tr("Evolve"));
  stop_action_ = this->addAction(QIcon(":/assets/stop.png"), tr("Stop"));
  reset_action_ = this->addAction(QIcon(":/assets/reset.png"), tr("Reset"));
  random_action_ = this->addAction(QIcon(":/assets/random.png"), tr("Random"));
  help_action_ = this->addAction(QIcon(":/assets/help.png"), tr("Help"));

  connect(evolve_action_, &QAction::triggered, this, &ToolBar::evolve_handler);
  connect(evolve_step_action_, &QAction::triggered, this,
          &ToolBar::evolve_step_handler);
  connect(reset_action_, &QAction::triggered, this, &ToolBar::reset_handler);

  connect(open_folder_action_, &QAction::triggered, this,
          &ToolBar::open_folder_handler);
  connect(stop_action_, &QAction::triggered, this, &ToolBar::stop_handler);
  connect(random_action_, &QAction::triggered, this, &ToolBar::random_signal);
  connect(help_action_, &QAction::triggered, this, &ToolBar::help_handler);
}

void ToolBar::evolve_handler() {
  emit evolve_signal();
}

void ToolBar::stop_handler() {
  emit stop_signal();
}

void ToolBar::evolve_step_handler() {
  emit evolve_step_signal();
}

void ToolBar::reset_handler() {
  emit reset_signal();
}

void ToolBar::open_folder_handler() {
  emit open_folder_signal();
}

void ToolBar::random_handler() {
  emit random_signal();
}

void ToolBar::help_handler() {
  QPointer<HelpWidget> help_widget_ = new HelpWidget();
  help_widget_->show();
}