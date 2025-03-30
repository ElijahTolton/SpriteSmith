#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "layermodel.h"
#include "qtablewidget.h"
#include <QMainWindow>
#include "sizedialog.h"
#include "spriteeditor.h"
#include <QColorDialog>
#include <tool.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(SizeDialog *setSizeWindow, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void initEditor(int canvasDim);
    void cloneLayer();
    void openColor();
    void setColor();

private:
    Ui::MainWindow *ui;
    QColorDialog* colorWindow;
    Tool* editTools;

    SpriteEditor *editor;  // Pointer to the sprite editor
    LayerModel *layerModel;

    // Get the tool tips and the icons for each of the buttons.
    void setUpIcons();
    void setUpConnections(const int canvasDim);
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
