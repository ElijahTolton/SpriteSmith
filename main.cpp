#include "mainwindow.h"
#include "sizedialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle("Fusion");

    SizeDialog setSizeWindow;
    setSizeWindow.setWindowTitle("Sprite Dimensions");

    MainWindow window(&setSizeWindow);
    window.setWindowTitle("SpriteSmith");

    setSizeWindow.exec();
    window.show();
    return app.exec();
}
