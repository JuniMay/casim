#include "gui/main_window.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow window;
    window.show();
    return a.exec();
}
