#include "mainwindow.h"
#include "layerdelegate.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPalette>
#include "frameview.h"
#include <QMouseEvent>
#include <QFileDialog>

/**
 * @brief Mainwindow that is displayed to the user
 *
 * This class provides functionalities for sprite and layer management, color selection,
 * animation preview, and interaction with various tools within the pixel editor.
 *
 * @authors Landon Huking, Dean Smith, Alex Lancaster, Canon Curtis, & Elijah Tolton
 * @date March 31, 2025
 *
 * Checked by Elijah Tolton
 */

MainWindow::MainWindow(SizeDialog *setSizeWindow, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    colorWindow = new QColorDialog(this);
    colorWindow->setOption(QColorDialog::ShowAlphaChannel);
    editTools = new Tool;
    layerView = new LayerView(this);
    frameWidgets.push_back(ui->frame1);
    activeFrame = ui->frame1;

    lastFrameIndex = 0;
    lastLayerIndex = 0;

    setUpIcons();

    connect(setSizeWindow, &SizeDialog::setSize, this, &MainWindow::initEditor);

    connect(ui->addLayer, &QPushButton::clicked, this, &MainWindow::cloneLayer);
    connect(ui->removeLayer, &QPushButton::clicked, ui->layerWidget, &LayerView::removeLayer);
    connect(layerView, &LayerView::removeLayerIndex, this, &MainWindow::removeLayer);
    connect(layerView, &LayerView::getLayerIndex, this, &MainWindow::removeLayer);

    connect(ui->addFrame, &QPushButton::clicked, this, &MainWindow::cloneFrame);
    connect(ui->removeFrame, &QPushButton::clicked, this, &MainWindow::removeFrame);
    connect(ui->frame1, &QPushButton::pressed, ui->frame1, &FrameView::changeIndex);
    connect(ui->frame1, &FrameView::getIndex, this, &MainWindow::updateCurrentFrame);

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
            QLabel* newLabel = new QLabel(QString("Layer %1").arg(lastLayerIndex), newLayer);
            newLabel->setGeometry(label->geometry());
        } else if (QPushButton *button = qobject_cast<QPushButton *>(child)) {
            newButton = new QPushButton(button->text(), newLayer);
            newButton->setGeometry(button->geometry());
            newButton->setStyleSheet(button->styleSheet());
        }
    }
    ui->layerView->addWidget(newLayer);

    connect(newLayer, &LayerView::removeLayerIndex, this, &MainWindow::removeLayer);
    connect(newButton, &QPushButton::clicked, newLayer, &LayerView::removeLayer);
}

void MainWindow::removeLayer(int layerIndex) {
    lastLayerIndex--;

    if (ui->layerView->count() > 1) {
        QLayoutItem *item = ui->layerView->takeAt(layerIndex);

        delete item->widget();
        for (; layerIndex < ui->layerView->count(); layerIndex++) {
            QLayoutItem *item = ui->layerView->itemAt(layerIndex);
            LayerView *layerView = qobject_cast<LayerView *>(item->widget());
            layerView->layerIndex = layerIndex;

            QLabel *label = layerView->findChild<QLabel *>();
            label->setText(QString("Layer %1").arg(layerIndex));
        }

        lastLayerIndex = ui->layerView->count() - 1;
    }
}

void MainWindow::cloneFrame() {
    lastFrameIndex++;
    qDebug() << lastFrameIndex;

    //Create a new QWidget and copy properties
    FrameView *newWidget = new FrameView(nullptr, lastFrameIndex);

    connect(newWidget, &QPushButton::clicked, newWidget, &FrameView::changeIndex);
    connect(newWidget, &FrameView::getIndex, this, &MainWindow::updateCurrentFrame);
    connect(newWidget, &FrameView::repaintSignal, sprite, &Sprite::sendFramePreview);
    connect(sprite, &Sprite::updateFrame, newWidget, &FrameView::displayPreview);

    sprite->frames->addFrame();
    ui->frameView->addWidget(newWidget);
    frameWidgets.push_back(newWidget);
}

void MainWindow::updateCurrentFrame(int index){
    ui->canvas->currentFrame = index;
    ui->canvas->repaint();

    activeFrame = frameWidgets[index];
    qDebug() << index;
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

    layerModel = new LayerModel(canvasDim, canvasDim); //TODO remove
    sprite = new Sprite(canvasDim, lastLayerIndex, this);

    ui->canvas->setSprite(sprite);
    setUpConnections(canvasDim);
}

void MainWindow::setUpConnections(const int canvasDim) {
    editTools = new Tool(ui->canvas, &sprite->frames->getFrame(ui->canvas->currentFrame).getLayerModel());

    connect(ui->mirror, &QPushButton::pressed, ui->canvas, &SpriteEditor::mirrorLayer);
    connect(ui->pencil, &QPushButton::pressed, this, &MainWindow::setColor);
    connect(ui->eraser, &QPushButton::pressed, editTools, &Tool::setErase);
    connect(ui->rotate, &QPushButton::pressed, [this]() {
        sprite->frames->getFrame(0).layers.rotateLayer();
        ui->canvas->repaint();
    });
    connect(ui->save, &QPushButton::pressed, this, &MainWindow::saveSprite);
    connect(ui->load, &QPushButton::pressed, this, &MainWindow::loadSprite);

    connect(ui->undo, &QPushButton::pressed, ui->canvas, &SpriteEditor::undo);
    connect(ui->redo, &QPushButton::pressed, ui->canvas, &SpriteEditor::redo);
    connect(layerModel, &LayerModel::layerChanged, ui->canvas, &SpriteEditor::repaint);

    connect(ui->fpsSlider, &QSlider::valueChanged, sprite, &Sprite::updateFramerate);
    connect(sprite, &Sprite::displayFrame, this, &MainWindow::setAnimationPreview);

    connect(ui->frame1, &FrameView::repaintSignal, sprite, &Sprite::sendFramePreview);
    connect(sprite, &Sprite::updateFrame, ui->frame1, &FrameView::displayPreview);
    connect(ui->canvas, &::SpriteEditor::pixelCLicked, editTools, &Tool::onEdit);

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
    ui->canvas->setColor(colorWindow->currentColor());
    editTools->setColor(colorWindow->currentColor());

    QPalette color = ui->colorPreview->palette();
    color.setColor(QPalette::Button, QColor(colorWindow->currentColor()));
    ui->colorPreview->setAutoFillBackground(true); // Important to fill the background
    ui->colorPreview->setPalette(color);
    ui->colorPreview->update(); // Refresh the button
}

void MainWindow::setAnimationPreview(QPixmap image) {
    if (ui->checkBox->isChecked()) {
        animationPreviewDimensions = image.size();
    }
    else {
        animationPreviewDimensions = ui->animationPreview->size();
    }

    ui->animationPreview->setPixmap(image.scaled(animationPreviewDimensions));
}

void MainWindow::saveSprite() {
    QString* filter = new QString("Sprite Sheet Project (*.ssp);;All Files (*)");
    QString saveFileName = QFileDialog::getSaveFileName(this, "SpriteSmith - Save",
                                                       "untitled.ssp", QDir::homePath(), filter);

    if (saveFileName.isEmpty()) {
        return;
    }

    if (!saveFileName.endsWith(".ssp", Qt::CaseSensitive)) {
        saveFileName += ".ssp";
    }

    sprite->save(saveFileName);
}

void MainWindow::loadSprite() {
    QString filter = "Sprite Sheet Project (*.ssp);;All Files (*.)";
    QString loadFile = QFileDialog::getOpenFileName(this, "SpriteSmith - Load;"
                                                    "", QDir::homePath(), filter);

    if (loadFile.isEmpty()) {
        return;
    }

    sprite->load(loadFile);

    qDebug() << sprite->frames->getFrames().front().getTopLayer().getImage().pixelColor(0,0);
    ui->canvas->setSprite(sprite);
    qDebug() << sprite->frames->getFrames().front().getTopLayer().getImage().pixelColor(0,0);
    ui->canvas->repaint();
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
