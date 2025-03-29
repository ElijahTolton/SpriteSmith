#include "spriteeditor.h"

SpriteEditor::SpriteEditor(QWidget *parent) : QTableWidget(parent) { }

void SpriteEditor::setCanvasSize(int rows, int cols) {

    // TODO - FIX BUG WITH HIGHER PIXEL COUNT AND CANVAS SIZE
    int pixelSize = CANVAS_SIZE / rows;

    setRowCount(rows);
    setColumnCount(cols);

    // Must manually set the size of each row and col
    for (int row = 0; row < rows; row++)
        setRowHeight(row, pixelSize);

    for (int col = 0; col < cols; col++)
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

void SpriteEditor::changeCellColor(QMouseEvent *event) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        QTableWidgetItem *item = itemAt(event->pos());
        if (!item) {
            item = new QTableWidgetItem();
            setItem(index.row(), index.column(), item);
        }
        item->setBackground(currentColor);
    }
}
