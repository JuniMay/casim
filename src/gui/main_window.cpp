
#include "gui/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  this->setWindowIcon(QIcon(":/assets/icon.ico"));
  this->setWindowTitle("Casim");

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

  timer_ = new QTimer(this);
  timer_->setInterval(100);

  connect(tool_bar_, &ToolBar::reset_signal, viewer_, &Viewer::reset_camera);

  automaton_ = QSharedPointer<casim::core::Automaton>(
      new casim::core::Automaton({500, 500}, "", 1));  // TODO

  viewer_->set_automaton(automaton_);

  connect(tool_bar_, &ToolBar::evolve_step_signal, this,
          &MainWindow::evolve_step);

  connect(tool_bar_, &ToolBar::open_folder_signal, file_tree_,
          &FileTree::open_folder);

  connect(tool_bar_, &ToolBar::evolve_signal, this, &MainWindow::evolve);

  connect(tool_bar_, &ToolBar::stop_signal, this, &MainWindow::stop_evolve);

  connect(tool_bar_, &ToolBar::random_signal, this,
          &MainWindow::random_pattern);

  connect(timer_, &QTimer::timeout, this, &MainWindow::evolve_step);

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

  connect(file_tree_, &FileTree::load_pattern_signal, this,
          &MainWindow::file_tree_load_pattern);

  connect(config_editor_, &ConfigEditor::pattern_add, this,
          &MainWindow::add_cell);

  connect(config_editor_, &ConfigEditor::pattern_load, this,
          &MainWindow::load_pattern);

  connect(config_editor_, &ConfigEditor::pattern_save, this,
          &MainWindow::save_pattern);

  connect(config_editor_, &ConfigEditor::pattern_reset, this,
          &MainWindow::reset_pattern);

  connect(config_editor_, &ConfigEditor::pattern_resize, this,
          &MainWindow::resize_automaton);
}

void MainWindow::evolve() {
  logger_->log("Start Evolving...");
  timer_->start();
}
void MainWindow::stop_evolve() {
  logger_->log("Stop Evolving.");
  timer_->stop();
}

void MainWindow::evolve_step() {
  automaton_->evolve();
  viewer_->display_automaton();
}

void MainWindow::load_script(const QString& script) {
  automaton_->set_script(script.toLocal8Bit().data());
  viewer_->reset_view();
  viewer_->display_automaton();
}

void MainWindow::add_cell(const size_t& x,
                          const size_t& y,
                          const size_t& z,
                          const uint32_t& state) {
  size_t dim = automaton_->get_dim();
  if (dim == 1) {
    automaton_->set_cell_state({x}, state);
  } else if (dim == 2) {
    automaton_->set_cell_state({y, x}, state);
  } else if (dim == 3) {
    automaton_->set_cell_state({z, y, x}, state);
  }
  viewer_->display_automaton();
}

void MainWindow::load_pattern() {
  QFileDialog dialog(this);
  QString path = dialog.getOpenFileName(this, tr("Open Pattern"), ".", "*.npy");

  if (path == "")
    return;
  logger_->log("Loading pattern from " + path);
  //  qDebug() << path;
  automaton_->load_pattern_from_file(path.toLocal8Bit().data());
  logger_->log("Done.");
  viewer_->reset_view();
  viewer_->display_automaton();
}

void MainWindow::file_tree_load_pattern(const QString& path) {
  logger_->log("Loading pattern from " + path);
  automaton_->load_pattern_from_file(path.toLocal8Bit().data());
  logger_->log("Done.");
  viewer_->reset_view();
  viewer_->display_automaton();
}

void MainWindow::save_pattern() {
  QFileDialog dialog(this);
  dialog.setDefaultSuffix(".npy");
  QString path = dialog.getSaveFileName(this, tr("Save Pattern"), ".", "*.npy");
  //  qDebug() << path;
  if (path == "")
    return;
  logger_->log("Saving pattern to " + path);
  automaton_->save_pattern_to_file(path.toLocal8Bit().data());
  logger_->log("Done.");
  viewer_->reset_view();
  viewer_->display_automaton();
}

void MainWindow::reset_pattern() {
  logger_->log("Reset pattern.");
  automaton_->reset();
  viewer_->reset_view();
  viewer_->display_automaton();
}

void MainWindow::random_pattern() {
  logger_->log("Randomizing pattern...");
  size_t state_cnt = automaton_->get_state_cnt();
  if (state_cnt == 0) {
    logger_->log("Randomizing failed: No states specified.");
    return;
  }
  logger_->log("Done.");
  std::vector<double> w;
  for (size_t i = 0; i < state_cnt; ++i) {
    w.push_back(100.0 / state_cnt);
  }
  automaton_->random(w);
  viewer_->reset_view();
  viewer_->display_automaton();
}

void MainWindow::resize_automaton(const size_t& depth,
                                  const size_t& height,
                                  const size_t& width) {
  size_t dim = automaton_->get_dim();
  if (dim == 1) {
    automaton_->set_shape({width});
  } else if (dim == 2) {
    automaton_->set_shape({height, width});
  } else if (dim == 3) {
    automaton_->set_shape({depth, height, width});
  }
  viewer_->reset_view();
  viewer_->display_automaton();
}