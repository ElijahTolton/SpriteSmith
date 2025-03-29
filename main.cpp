#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SizeDialog setSizeWindow;
    MainWindow window(&setSizeWindow);
    setSizeWindow.exec();
    window.show();
    return app.exec();
}
