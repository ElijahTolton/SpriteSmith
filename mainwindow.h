#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtablewidget.h"
#include <QMainWindow>
#include "spriteeditor.h"  // Include the sprite editor header
#include "sizedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(SizeDialog *setSizeWindow, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Makes cells lighter when hovered over.
    void cellHover(QTableWidgetItem* item);

    // TODO Make this slot receive the color from the model
    void displayColor(int row, int col);

public slots:
    void initEditor(int canvasDim);

private:
    Ui::MainWindow *ui;
    SpriteEditor *editor;  // Pointer to the sprite editor

    // Get the tool tips and the icons for each of the buttons.
    void setUpIcons();

    // Set size of cnavs and cells and allow mouse hovering.
    void setUpCanvas(int canvasWidth, int canvasHeight);
};

#endif // MAINWINDOW_H
