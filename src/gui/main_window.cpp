
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

    connect(tool_bar_, &ToolBar::resetSignal, viewer_, &Viewer::resetCamera);

    automaton_ = QSharedPointer<casim::core::Automaton>(
        new casim::core::Automaton({500, 500}, "", 1));  // TODO

    viewer_->setAutomaton(automaton_);

    connect(tool_bar_, &ToolBar::evolveStepSignal, this,
            &MainWindow::evolveStep);

    connect(tool_bar_, &ToolBar::openFolderSignal, file_tree_,
            &FileTree::openFolder);

    connect(tool_bar_, &ToolBar::evolveSignal, this, &MainWindow::evolve);

    connect(tool_bar_, &ToolBar::stopSignal, this, &MainWindow::stopEvolve);

    connect(tool_bar_, &ToolBar::randomSignal, this,
            &MainWindow::randomPattern);

    connect(timer_, &QTimer::timeout, this, &MainWindow::evolveStep);

    connect(viewer_, &Viewer::yawChanged, config_editor_,
            &ConfigEditor::viewerYawChangedFromViewer);

    connect(viewer_, &Viewer::pitchChanged, config_editor_,
            &ConfigEditor::viewerPitchChangedFromViewer);

    connect(viewer_, &Viewer::sensitivityChanged, config_editor_,
            &ConfigEditor::viewerSensitivityChangedFromViewer);

    connect(viewer_, &Viewer::moveSpeedChanged, config_editor_,
            &ConfigEditor::viewerMoveSpeedChangedFromViewer);

    connect(viewer_, &Viewer::cellSizeChanged, config_editor_,
            &ConfigEditor::viewerCellSizeChangedFromViewer);

    connect(config_editor_, &ConfigEditor::viewerYawChangedFromConfig, viewer_,
            &Viewer::setYaw);

    connect(config_editor_, &ConfigEditor::viewerPitchChangedFromConfig,
            viewer_, &Viewer::setPitch);

    connect(config_editor_, &ConfigEditor::viewerSensitivityChangedFromConfig,
            viewer_, &Viewer::setSensitivity);

    connect(config_editor_, &ConfigEditor::viewerMoveSpeedChangedFromConfig,
            viewer_, &Viewer::setMoveSpeed);

    connect(config_editor_, &ConfigEditor::viewerCellSizeChangedFromConfig,
            viewer_, &Viewer::setCellSize);

    connect(config_editor_, &ConfigEditor::viewerViewModeChangedFromConfig,
            viewer_, &Viewer::setViewMode);

    connect(file_tree_, &FileTree::loadScriptSignal, script_editor_,
            &ScriptEditor::loadScript);

    connect(file_tree_, &FileTree::loadScriptSignal, this,
            &MainWindow::loadScript);

    connect(file_tree_, &FileTree::loadPatternSignal, this,
            &MainWindow::fileTreeLoadPattern);

    connect(config_editor_, &ConfigEditor::patternAdd, this,
            &MainWindow::addCell);

    connect(config_editor_, &ConfigEditor::patternLoad, this,
            &MainWindow::loadPattern);

    connect(config_editor_, &ConfigEditor::patternSave, this,
            &MainWindow::savePattern);

    connect(config_editor_, &ConfigEditor::patternReset, this,
            &MainWindow::resetPattern);

    connect(config_editor_, &ConfigEditor::patternResize, this,
            &MainWindow::resizeAutomaton);
}

void MainWindow::evolve() {
    logger_->log("Start Evolving...");
    timer_->start();
}
void MainWindow::stopEvolve() {
    logger_->log("Stop Evolving.");
    timer_->stop();
}

void MainWindow::evolveStep() {
    bool success = automaton_->evolve();
    if (!success) {
        logger_->log("Error occurred while evolving, stop.");
        stopEvolve();
        return;
    }
    viewer_->displayAutomaton();
}

void MainWindow::loadScript(const QString& script) {
    automaton_->setScript(script.toLocal8Bit().data());
    viewer_->resetView();
    viewer_->displayAutomaton();
}

void MainWindow::addCell(const size_t& x,
                         const size_t& y,
                         const size_t& z,
                         const uint32_t& state) {
    size_t dim = automaton_->getDim();
    if (dim == 1) {
        automaton_->setCellState({x}, state);
    } else if (dim == 2) {
        automaton_->setCellState({y, x}, state);
    } else if (dim == 3) {
        automaton_->setCellState({z, y, x}, state);
    }
    viewer_->displayAutomaton();
}

void MainWindow::loadPattern() {
    QFileDialog dialog(this);
    QString path =
        dialog.getOpenFileName(this, tr("Open Pattern"), ".", "*.npy");

    if (path == "")
        return;
    logger_->log("Loading pattern from " + path);
    //  qDebug() << path;
    automaton_->loadPatternFromFile(path.toLocal8Bit().data());
    logger_->log("Done.");
    viewer_->resetView();
    viewer_->displayAutomaton();
}

void MainWindow::fileTreeLoadPattern(const QString& path) {
    logger_->log("Loading pattern from " + path);
    automaton_->loadPatternFromFile(path.toLocal8Bit().data());
    logger_->log("Done.");
    viewer_->resetView();
    viewer_->displayAutomaton();
}

void MainWindow::savePattern() {
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".npy");
    QString path =
        dialog.getSaveFileName(this, tr("Save Pattern"), ".", "*.npy");
    //  qDebug() << path;
    if (path == "")
        return;
    logger_->log("Saving pattern to " + path);
    automaton_->savePatternToFile(path.toLocal8Bit().data());
    logger_->log("Done.");
    viewer_->resetView();
    viewer_->displayAutomaton();
}

void MainWindow::resetPattern() {
    logger_->log("Reset pattern.");
    automaton_->reset();
    viewer_->resetView();
    viewer_->displayAutomaton();
}

void MainWindow::randomPattern() {
    logger_->log("Randomizing pattern...");
    size_t state_cnt = automaton_->getStateCnt();
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
    viewer_->resetView();
    viewer_->displayAutomaton();
}

void MainWindow::resizeAutomaton(const size_t& depth,
                                  const size_t& height,
                                  const size_t& width) {
    size_t dim = automaton_->getDim();
    if (dim == 1) {
        automaton_->setShape({width});
    } else if (dim == 2) {
        automaton_->setShape({height, width});
    } else if (dim == 3) {
        automaton_->setShape({depth, height, width});
    }
    viewer_->resetView();
    viewer_->displayAutomaton();
}
