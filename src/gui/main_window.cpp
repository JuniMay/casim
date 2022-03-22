
#include "gui/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  this->resize(1080, 720);
  QPointer<QDockWidget> dock;
  viewer_ = new Viewer(this);
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
      new casim::core::Automaton({100, 100}, "", 1));  // TODO
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
  connect(viewer_, &Viewer::cell_size_changed, config_editor_,
          &ConfigEditor::viewer_cell_size_changed_from_viewer);

  connect(config_editor_, &ConfigEditor::viewer_yaw_changed_from_config,
          viewer_, &Viewer::set_yaw);
  connect(config_editor_, &ConfigEditor::viewer_pitch_changed_from_config,
          viewer_, &Viewer::set_pitch);
  connect(config_editor_, &ConfigEditor::viewer_sensitivity_changed_from_config,
          viewer_, &Viewer::set_sensitivity);
  connect(config_editor_, &ConfigEditor::viewer_move_speed_changed_from_config,
          viewer_, &Viewer::set_move_speed);
  connect(config_editor_, &ConfigEditor::viewer_cell_size_changed_from_config,
          viewer_, &Viewer::set_cell_size);
  connect(config_editor_, &ConfigEditor::viewer_view_mode_changed_from_config,
          viewer_, &Viewer::set_view_mode);

  connect(file_tree_, &FileTree::load_script_signal, script_editor_,
          &ScriptEditor::load_script);

  connect(file_tree_, &FileTree::load_script_signal, this,
          &MainWindow::load_script);

  connect(config_editor_, &ConfigEditor::pattern_add, this,
          &MainWindow::add_cell);
  connect(config_editor_, &ConfigEditor::pattern_load, this,
          &MainWindow::load_pattern);
  connect(config_editor_, &ConfigEditor::pattern_save, this,
          &MainWindow::save_pattern);
  connect(config_editor_, &ConfigEditor::pattern_reset, this,
          &MainWindow::reset_pattern);
}

void MainWindow::evolve() {
  automaton_->evolve_by_step();
  viewer_->display_automaton();
}

void MainWindow::load_script(const QString& script) {
  viewer_->reset_view();
  automaton_->set_script(script.toLocal8Bit().data());

  //  automaton_->set_cell_state({15, 10}, 3);

  //  automaton_->set_cell_state({14, 11}, 3);
  //  automaton_->set_cell_state({14, 12}, 1);
  //  automaton_->set_cell_state({14, 13}, 2);
  //  automaton_->set_cell_state({14, 14}, 3);
  //  automaton_->set_cell_state({14, 15}, 3);

  //  automaton_->set_cell_state({15, 16}, 3);

  //  automaton_->set_cell_state({16, 11}, 3);
  //  automaton_->set_cell_state({16, 12}, 3);
  //  automaton_->set_cell_state({16, 13}, 2);
  //  automaton_->set_cell_state({16, 14}, 1);
  //  automaton_->set_cell_state({16, 15}, 3);
  automaton_->set_cell_state({15, 10}, 1);

  automaton_->set_cell_state({14, 11}, 1);
  automaton_->set_cell_state({14, 12}, 1);
  automaton_->set_cell_state({14, 13}, 1);
  automaton_->set_cell_state({14, 14}, 1);
  automaton_->set_cell_state({14, 15}, 1);

  automaton_->set_cell_state({15, 16}, 1);

  automaton_->set_cell_state({16, 11}, 1);
  automaton_->set_cell_state({16, 12}, 1);
  automaton_->set_cell_state({16, 13}, 1);
  automaton_->set_cell_state({16, 14}, 1);
  automaton_->set_cell_state({16, 15}, 1);
  viewer_->display_automaton();
}

void MainWindow::add_cell(const size_t& x, const size_t& y, const size_t& z,
                          const uint32_t& state) {
  size_t dim = automaton_->get_dim();
  if (dim == 1) {
    automaton_->set_cell_state({x}, state);
  } else if (dim == 2) {
    automaton_->set_cell_state({y, x}, state);
  } else if (dim == 3) {
    automaton_->set_cell_state({z, y, z}, state);
  }
  viewer_->display_automaton();
}
void MainWindow::load_pattern() {}
void MainWindow::save_pattern() {}
void MainWindow::reset_pattern() {
  automaton_->reset();
  viewer_->reset_view();
  viewer_->display_automaton();
}
