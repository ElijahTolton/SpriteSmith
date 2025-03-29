#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 * @brief MainWindow::MainWindow
 * Main controller for SpriteSmith which makes connections between the model
 * UI and setUp icons.
 *
 * SpirteSmith UI contains the following tools:
 * pencil, eraser, undo, redo, mirror, rotate, save and load.
 *
 * It displays a image preview of all frames in the current sprite.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpIcons();

    setUpIcons();

    // Todo get the inputs from the user
    setUpCanvas(25, 25);

    connect(ui->canvas,
            &QTableWidget::itemEntered,
            this,
            &MainWindow::cellHover
            );

    // TODO when send info to model adjust and send back color
    // to the view.
    connect(ui->canvas,
            &QTableWidget::cellPressed,
            this,
            &MainWindow::displayColor
            );

}

<<<<<<< HEAD
void MainWindow::initEditor(int canvasDim) {
    //editor = new SpriteEditor(this);
    ui->canvas->setCanvasSize(canvasDim, canvasDim);
}

MainWindow::~MainWindow() {
=======
MainWindow::~MainWindow()
{
>>>>>>> c5be859 (Revert "Merge branch 'main' of https://github.com/UofU-CS3505/cs3505-assignment8-deanasmith into Landon")
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

void MainWindow::cellHover(QTableWidgetItem* item){
    // Intially set cell color to black
    // TODO: We will need to query the model for the cells color
    // to make it lighter
    QColor color(Qt::gray);

    // Make cell 1.5 times lighter
    item->setBackground(color.lighter(150));
}

void MainWindow::setUpCanvas(int canvasWidth, int canvasHeight){
    auto canvas = ui->canvas;

    canvas->setShowGrid(false);
    canvas->horizontalHeader()->setVisible(false);
    canvas->verticalHeader()->setVisible(false);
    canvas->setStyleSheet(
        "QTableWidget::item { border: none;}"
        "QTableView { border: none;}"
        );
    canvas->setMouseTracking(true);

    canvas->setRowCount(canvasWidth);
    canvas->setColumnCount(canvasHeight);
    canvas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < canvas->columnCount(); i++){
        canvas->setColumnWidth(i, 20);
    }
    for(int i = 0; i < canvas->columnCount(); i++){
        canvas->setColumnWidth(i, 20);
    }
}

void MainWindow::displayColor(int row, int col){
    QColor color(255, 0, 0);
    QBrush brush(color);

    qDebug() << brush.color();

    QTableWidgetItem* item = ui->canvas->item(row, col);
    qDebug() << "entered";
    if(item){
        item->setBackground(brush);
        qDebug() << "Item not Null";
    }else{
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setBackground(brush);
        ui->canvas->setItem(row, col, item);
        item->setText("Hello World");
        qDebug() << item->background().color();
    }
}
