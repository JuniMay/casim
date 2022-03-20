
#include "gui/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  // widget_ = new QWidget(this);
  // this->setCentralWidget(widget_);
  this->resize(1080, 720);
  QPointer<QDockWidget> dock;
  viewer_ = new Viewer(this);
  // viewer_->setFixedSize(400, 300);
  this->setCentralWidget(viewer_);

  dock = new QDockWidget(this);
  config_editor_ = new ConfigEditor(dock);
  dock->setWindowTitle(tr("Configuration"));
  dock->setWidget(config_editor_);
  this->addDockWidget(Qt::RightDockWidgetArea, dock);

  dock = new QDockWidget(this);
  script_editor_ = new ScriptEditor(dock);
  dock->setWindowTitle(tr("Script Editor"));
  dock->setWidget(script_editor_);
  this->addDockWidget(Qt::RightDockWidgetArea, dock);

  dock = new QDockWidget(this);
  logger_ = new Logger(dock);
  dock->setWindowTitle(tr("Information"));
  dock->setWidget(logger_);
  this->addDockWidget(Qt::BottomDockWidgetArea, dock);

  dock = new QDockWidget(this);
  file_tree_ = new FileTree(dock);
  dock->setWindowTitle(tr("File Tree"));
  dock->setWidget(file_tree_);
  this->addDockWidget(Qt::LeftDockWidgetArea, dock);

  this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
  this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

  tool_bar_ = new ToolBar(this);
  this->addToolBar(tool_bar_);

  connect(tool_bar_, &ToolBar::reset_signal, viewer_, &Viewer::reset_camera);

  automaton_ = QSharedPointer<casim::core::Automaton>(
      new casim::core::Automaton({30, 30}, "", 1));
  viewer_->set_automaton(automaton_);
  connect(tool_bar_, &ToolBar::evolve_signal, this, &MainWindow::evolve);

  connect(viewer_, &Viewer::yaw_changed, config_editor_,
          &ConfigEditor::viewer_yaw_changed_from_viewer);
  connect(viewer_, &Viewer::pitch_changed, config_editor_,
          &ConfigEditor::viewer_pitch_changed_from_viewer);
  connect(viewer_, &Viewer::sensitivity_changed, config_editor_,
          &ConfigEditor::viewer_sensitivity_changed_from_viewer);
  connect(viewer_, &Viewer::move_speed_changed, config_editor_,
          &ConfigEditor::viewer_move_speed_changed_from_viewer);

  connect(config_editor_, &ConfigEditor::viewer_yaw_changed_from_config,
          viewer_, &Viewer::set_yaw);
  connect(config_editor_, &ConfigEditor::viewer_pitch_changed_from_config,
          viewer_, &Viewer::set_pitch);
  connect(config_editor_, &ConfigEditor::viewer_sensitivity_changed_from_config,
          viewer_, &Viewer::set_sensitivity);
  connect(config_editor_, &ConfigEditor::viewer_move_speed_changed_from_config,
          viewer_, &Viewer::set_move_speed);

  connect(file_tree_, &FileTree::load_script_signal, script_editor_,
          &ScriptEditor::load_script);

  connect(file_tree_, &FileTree::load_script_signal, this,
          &MainWindow::load_script);

  automaton_->set_cell_state({15, 10}, 3);

  automaton_->set_cell_state({14, 11}, 3);
  automaton_->set_cell_state({14, 12}, 1);
  automaton_->set_cell_state({14, 13}, 2);
  automaton_->set_cell_state({14, 14}, 3);
  automaton_->set_cell_state({14, 15}, 3);

  automaton_->set_cell_state({15, 16}, 3);

  automaton_->set_cell_state({16, 11}, 3);
  automaton_->set_cell_state({16, 12}, 3);
  automaton_->set_cell_state({16, 13}, 2);
  automaton_->set_cell_state({16, 14}, 1);
  automaton_->set_cell_state({16, 15}, 3);
}

void MainWindow::evolve() {
  automaton_->evolve_by_step();
  qDebug() << "evolve ok";
  viewer_->display_automaton();
}

void MainWindow::load_script(const QString& script) {
  qDebug() << "load!";
  automaton_->set_script(script.toLocal8Bit().data());
}
