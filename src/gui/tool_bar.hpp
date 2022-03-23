#ifndef CASIM_GUI_TOOL_BAR_HPP_
#define CASIM_GUI_TOOL_BAR_HPP_

#include "gui/common.hpp"

class ToolBar : public QToolBar {
  Q_OBJECT
 public:
  ToolBar(QWidget* parent = nullptr);

 signals:
  void evolve_signal();
  void stop_signal();
  void evolve_step_signal();
  void reset_signal();
  void open_folder_signal();
  void random_signal();

 public slots:
  void evolve_handler();
  void stop_handler();
  void evolve_step_handler();
  void reset_handler();
  void open_folder_handler();
  void random_handler();

 private:
  QPointer<QAction> evolve_action_;
  QPointer<QAction> evolve_step_action_;
  QPointer<QAction> stop_action_;
  QPointer<QAction> open_folder_action_;
  QPointer<QAction> reset_action_;
  QPointer<QAction> random_action_;
};

#endif  // CASIM_GUI_TOOL_BAR_HPP_
