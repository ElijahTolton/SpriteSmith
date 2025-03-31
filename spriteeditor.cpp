#include "spriteeditor.h"
#include <QApplication>
#include "layereditcommand.h"
#include "layermodel.h"

SpriteEditor::SpriteEditor(QWidget *parent)
    : QTableWidget(parent) { }

void SpriteEditor::setCanvasSize() {

    // height or width / rowCount or columnCount can be exchanged since canvas should be square
    calculateCanvasSizeAdjustment();

    int pixelSize = height() / rowCount();

    // Allows cells to "stretch" to the canvas size
    verticalHeader()->setMinimumSectionSize(0);
    horizontalHeader()->setMinimumSectionSize(0);

    // Must manually set the size of each row and col
    for (int row = 0; row < rowCount(); row++)
        setRowHeight(row, pixelSize);

    for (int col = 0; col < columnCount(); col++)
        setColumnWidth(col, pixelSize);

}

void SpriteEditor::mousePressEvent(QMouseEvent *event) {
    QImage image = sprite->frames->getFrame(0).layers.getLayer(0).getImage();
    if (image.isNull()) {
        qDebug() << "Error: getImage() returned a null image!";
        return;
    }

    //copy current JSON for undo stack
    uneditedJSON = sprite->frames->getFrame(0).layers.getLayer(0).toJSON();

    setCanvasContents(sprite->frames->getFrame(0).layers.getLayer(0).getImage());
    changeCellColor(event);

    emit updatePreviews();
}

void SpriteEditor::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        setCanvasContents(sprite->frames->getFrame(0).layers.getLayer(0).getImage());
        changeCellColor(event);
    }
}

void SpriteEditor::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() & Qt::LeftButton) {
        Layer& tempLayer = sprite->frames->getFrame(0).layers.getLayer(0);
        LayerEditCommand* undoCommand = new LayerEditCommand(tempLayer, uneditedJSON, tempLayer.toJSON());
        undoStack.push(undoCommand);
    }
}

void SpriteEditor::undo() {
    undoStack.undo();
    repaint();
}

void SpriteEditor::redo() {
    undoStack.redo();
    repaint();
}

void SpriteEditor::setColor(QColor color) {
    currentColor = color;
}

void SpriteEditor::changeCellColor(QMouseEvent *event) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        QTableWidgetItem *item = itemAt(event->pos());
        if (!item) {
            item = new QTableWidgetItem();
            setItem(index.row(), index.column(), item);
        }

        sprite->frames->getFrame(0).layers.drawPixel(currentColor, index.column(), index.row());

        setCanvasContents(sprite->frames->getFrame(0).layers.getLayer(0).getImage());

        update();  // Refresh UI to apply changes
        emit pixelCLicked(event->pos());
    }
}

void SpriteEditor::setCanvasContents(QImage image) {

    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor color = image.pixelColor(x, y);  // Get the pixel color

            QModelIndex index = model()->index(y, x);

            // Ensure there is an item at this index
            QTableWidgetItem *item = itemFromIndex(index);
            if (!item) {
                item = new QTableWidgetItem();
                setItem(index.row(), index.column(), item);
            }

            // Set the background color of the item to match the pixel color
            item->setBackground(color);
            item->setData(Qt::UserRole, color);
        }
    }
}

void SpriteEditor::repaint() {
    // Refresh the contents of the canvas based on the current image in the layer model
    setCanvasContents(sprite->frames->getFrame(0).layers.getLayer(0).getImage());

    // After setting the contents, trigger the widget to repaint itself
    update();
}

void SpriteEditor::mirrorLayer() {
    sprite->frames->getFrame(0).layers.getLayer(0).mirror();
    repaint();
}

void SpriteEditor::setSprite(Sprite *spriteIn) {
    sprite = spriteIn;

    setRowCount(sprite->canvasDimension);
    setColumnCount(sprite->canvasDimension);
}

void SpriteEditor::calculateCanvasSizeAdjustment() {

    double pixelSize = (double)height() / (double)rowCount();
    double fractionalPart = pixelSize - (int)pixelSize; // Get the decimal part
    double canvasSizeAdjustment = 1.0 - fractionalPart; // Compute 1 - fractional part

    if(fractionalPart != 0) {
        int newCanvasSize = height() + canvasSizeAdjustment * rowCount();
        resize(newCanvasSize, newCanvasSize);
    }
}
