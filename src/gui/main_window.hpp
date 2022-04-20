#ifndef CASIM_GUI_MAIN_WINDOW_HPP_
#define CASIM_GUI_MAIN_WINDOW_HPP_

#include "file_tree.hpp"
#include "gui/common.hpp"
#include "gui/config_editor.hpp"
#include "gui/logger.hpp"
#include "gui/script_editor.hpp"
#include "gui/tool_bar.hpp"
#include "gui/viewer.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QWidget* parent = nullptr);

   public slots:
    void loadScript(const QString& script);
    void evolve();
    void stopEvolve();
    void evolveStep();

    void addCell(const size_t& x,
                 const size_t& y,
                 const size_t& z,
                 const uint32_t& state);
    void loadPattern();
    void fileTreeLoadPattern(const QString& path);
    void savePattern();
    void resetPattern();
    void randomPattern();
    void resizeAutomaton(const size_t& depth,
                         const size_t& height,
                         const size_t& width);

   private:
    QPointer<QWidget> widget_;

    QPointer<ScriptEditor> script_editor_;

    QPointer<ConfigEditor> config_editor_;

    QPointer<FileTree> file_tree_;

    QPointer<Viewer> viewer_;

    QPointer<Logger> logger_;

    QPointer<ToolBar> tool_bar_;

    QSharedPointer<casim::core::Automaton> automaton_;

    QPointer<QTimer> timer_;
};

#endif
