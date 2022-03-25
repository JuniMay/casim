#ifndef CASIM_GUI_HELP_WINDOW_HPP_
#define CASIM_GUI_HELP_WINDOW_HPP_

#include "gui/common.hpp"

class HelpWidget : public QWidget {
  Q_OBJECT
 public:
  HelpWidget(QWidget* parent = nullptr);

 public slots:

  void xtensor_handler();
  void xtl_handler();
  void casim_handler();
  void lua_handler();
  void qt_handler();
  void freeglut_handler();

 private:
  QPointer<QVBoxLayout> layout_;
  QPointer<QPushButton> xtensor_button_;
  QPointer<QPushButton> xtl_button_;
  QPointer<QPushButton> lua_button_;
  QPointer<QPushButton> casim_button_;
  QPointer<QPushButton> qt_button_;
  QPointer<QPushButton> freeglut_button_;
};

#endif  // CASIM_GUI_HELP_WINDOW_HPP_