#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sizedialog.h"
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

private:
    Ui::MainWindow *ui;
    QColorDialog* colorSelect;
    Tool* editTools;

    // Get the tool tips and the icons for each of the buttons.
    void setUpIcons();
    void setUpConnections(const int canvasDim);
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
