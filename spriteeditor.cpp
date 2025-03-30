#include "spriteeditor.h"
#include <QApplication>

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
    setCanvasContents(QImage(columnCount(), rowCount(), QImage::Format_RGBA8888));
    changeCellColor(event);
}

void SpriteEditor::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        setCanvasContents(QImage(columnCount(), rowCount(), QImage::Format_RGBA8888));
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
        // Store border color
        item->setData(Qt::UserRole, currentColor);  // Store as QColor

        update();  // Refresh UI to apply changes
        emit pixelCLicked(event->pos());

        QApplication::processEvents();
    }
}

void SpriteEditor::setCanvasContents(QImage t_image) {
    int t_width = t_image.width();
    int t_height = t_image.height();

    QImage image(t_width, t_height, QImage::Format_RGBA8888);

    int width = image.width();
    int height = image.height();

    // Fill the image with alternating colors (red and blue for simplicity)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor color = ((x + y) % 2 == 0) ? QColor(255, 255, 0) : QColor(0, 255, 255);
            image.setPixelColor(x, y, color);
        }
    }

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

    //update();  // Refresh the UI to apply the changes
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
