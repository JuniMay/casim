
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
}
