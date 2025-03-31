#include "mainwindow.h"
#include "layerdelegate.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QPalette>
#include "tool.h"
#include "frameview.h"
#include <QMouseEvent>

MainWindow::MainWindow(SizeDialog *setSizeWindow, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    colorWindow = new QColorDialog(this);
    colorWindow->setOption(QColorDialog::ShowAlphaChannel);
    editTools = new Tool;
    layerView = new LayerView(this);
    lastFrameIndex = 0;
    lastLayerIndex = 0;

    setUpIcons();

    connect(setSizeWindow, &SizeDialog::setSize, this, &MainWindow::initEditor);
    connect(ui->addLayer, &QPushButton::clicked, this, &MainWindow::cloneLayer);
    connect(ui->removeLayer, &QPushButton::clicked, ui->layerWidget, &LayerView::removeLayer);
    connect(layerView, &LayerView::getLayerIndex, this, &MainWindow::removeLayer);
    connect(ui->addFrame, &QPushButton::clicked, this, &MainWindow::cloneFrame);
    connect(ui->removeFrame, &QPushButton::clicked, this, &MainWindow::removeFrame);
    connect(ui->frame1, &QPushButton::clicked, ui->frame1, &FrameView::changeIndex);

    connect(ui->colorPicker, &QPushButton::pressed, this, &MainWindow::openColor);
    connect(colorWindow, &QColorDialog::currentColorChanged, this, &MainWindow::setColor);

}

void MainWindow::cloneLayer() {
    lastLayerIndex++;

    LayerView *originalLayer = ui->layerWidget;
    QPushButton *newButton;

    // Clone the widget by creating a new instance and copying properties
    LayerView *newLayer = new LayerView(lastLayerIndex);
    newLayer->setMinimumSize(originalLayer->minimumSize());
    newLayer->setMaximumSize(originalLayer->maximumSize());
    newLayer->setStyleSheet(originalLayer->styleSheet());

    // Copy the child widgets (labels, buttons, checkboxes)
    for (QObject *child : originalLayer->children()) {
        if (QLabel *label = qobject_cast<QLabel *>(child)) {
            QLabel *newLabel = new QLabel(label->text(), newLayer);
            newLabel->setGeometry(label->geometry());
        } else if (QPushButton *button = qobject_cast<QPushButton *>(child)) {
            newButton = new QPushButton(button->text(), newLayer);
            newButton->setGeometry(button->geometry());
            newButton->setStyleSheet(button->styleSheet());
        }
    }
    ui->layerView->addWidget(newLayer);

    connect(newLayer, &LayerView::getLayerIndex, this, &MainWindow::removeLayer);
    connect(newButton, &QPushButton::clicked, newLayer, &LayerView::removeLayer);
}

void MainWindow::removeLayer(int layerIndex) {
    lastLayerIndex--;
    qDebug() << "removeLayer hit";
    if (ui->layerView->count() > 1) {
        QLayoutItem *item = ui->layerView->takeAt(layerIndex);

        delete item->widget();
    }
}

void MainWindow::cloneFrame() {
    lastFrameIndex++;

    //Create a new QWidget and copy properties
    FrameView *newWidget = new FrameView(lastFrameIndex);

    connect(newWidget, &QPushButton::clicked, newWidget, &FrameView::changeIndex);
    ui->frameView->addWidget(newWidget);
}

void MainWindow::removeFrame(){
    if (ui->frameView->count() > 1) {
        QLayoutItem *item = ui->frameView->takeAt(ui->frameView->count() - 1); // Get the last item

        delete item->widget(); // Delete the widget

        lastFrameIndex--;
    }
}

void MainWindow::mirror(){
    emit requestMirror(0);
}

void MainWindow::initEditor(int canvasDim) {
    ui->canvas->setRowCount(canvasDim);
    ui->canvas->setColumnCount(canvasDim);
    ui->canvas->setCanvasSize();
    ui->canvas->setItemDelegate(new LayerDelegate(ui->canvas));

    layerModel = new LayerModel(canvasDim, canvasDim);
    ui->canvas->setLayerModel(layerModel);

    setUpConnections(canvasDim);
}

void MainWindow::setUpConnections(const int canvasDim) {
    editTools = new Tool(ui->canvas, new LayerModel(canvasDim, canvasDim));
    connect(ui->mirror, &QPushButton::pressed, ui->canvas, &SpriteEditor::mirrorLayer);
    connect(ui->pencil, &QPushButton::pressed, this, &MainWindow::setColor);
    connect(ui->eraser, &QPushButton::pressed, editTools, &Tool::setErase);
    connect(ui->rotate, &QPushButton::pressed, layerModel, &LayerModel::rotateLayer);
    connect(layerModel, &LayerModel::layerChanged, ui->canvas, &SpriteEditor::repaint);


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

void MainWindow::openColor() {
    colorWindow->open();
}

void MainWindow::setColor() {
    editTools->setColor(colorWindow->currentColor());

    QPalette color = ui->colorPreview->palette();
    color.setColor(QPalette::Button, QColor(colorWindow->currentColor()));
    ui->colorPreview->setAutoFillBackground(true); // Important to fill the background
    ui->colorPreview->setPalette(color);
    ui->colorPreview->update(); // Refresh the button
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
