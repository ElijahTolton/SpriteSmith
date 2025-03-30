#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(SizeDialog *setSizeWindow, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpIcons();

    connect(setSizeWindow, &SizeDialog::setSize, this, &MainWindow::initEditor);

}

void MainWindow::initEditor(int canvasDim) {
    ui->canvas->setRowCount(canvasDim);
    ui->canvas->setColumnCount(canvasDim);
    ui->canvas->setCanvasSize();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpIcons(){
    ui->pencil->setIcon(QIcon(":/icons/pencil"));
    ui->pencil->setIconSize(ui->pencil->size() * 2);
    ui->pencil->setToolTip("Draw");

    ui->eraser->setIcon(QIcon(":/icons/eraser"));
    ui->eraser->setIconSize(ui->eraser->size() * 2);
    ui->eraser->setToolTip("Erase");

    ui->undo->setIcon(QIcon(":/icons/undo"));
    ui->undo->setIconSize(ui->undo->size() * 2);
    ui->undo->setToolTip("Undo");

    ui->redo->setIcon(QIcon(":/icons/redo"));
    ui->redo->setIconSize(ui->redo->size() * 2);
    ui->redo->setToolTip("Redo");

    ui->mirror->setIcon(QIcon(":/icons/mirror"));
    ui->mirror->setIconSize(ui->redo->size() * 2);
    ui->mirror->setToolTip("Mirror");

    ui->rotate->setIcon(QIcon(":/icons/rotate"));
    ui->rotate->setIconSize(ui->rotate->size() * 2);
    ui->rotate->setToolTip("Rotate");

    ui->save->setIcon(QIcon(":/icons/save"));
    ui->save->setIconSize(ui->rotate->size() * 2);
    ui->save->setToolTip("Save");

    ui->load->setIcon(QIcon(":/icons/load"));
    ui->load->setIconSize(ui->rotate->size() * 2);
    ui->load->setToolTip("Load");
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quit", "Are you sure you want to quit?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }

    else {
        event->ignore();
    }
}
