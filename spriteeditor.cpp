#include "spriteeditor.h"

SpriteEditor::SpriteEditor(QWidget *parent) : QTableWidget(parent) { }

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
    changeCellColor(event);
}

void SpriteEditor::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        changeCellColor(event);
    }
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

        // Set background color
        item->setBackground(currentColor);
<<<<<<< HEAD

        // Store border color
        item->setData(Qt::UserRole, currentColor);  // Store as QColor

        update();  // Refresh UI to apply changes
=======
        emit pixelCLicked(event->pos());
>>>>>>> Landon
    }
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
