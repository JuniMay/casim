#ifndef CASIM_GUI_HELP_WINDOW_HPP_
#define CASIM_GUI_HELP_WINDOW_HPP_

#include "gui/common.hpp"

class HelpWidget : public QWidget {
    Q_OBJECT
   public:
    HelpWidget(QWidget* parent = nullptr);

   public slots:

    void xtensorHandler();
    void xtlHandler();
    void casimHandler();
    void luaHandler();
    void qtHandler();
    void freeglutHandler();

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