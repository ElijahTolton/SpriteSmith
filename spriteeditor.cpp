#include "spriteeditor.h"


SpriteEditor::SpriteEditor(QWidget *parent)
    : SpriteEditor(100, 100, parent)
{
}

SpriteEditor::SpriteEditor(int rows, int cols, QWidget *parent)
    : QTableWidget(rows, cols, parent)
{
    //setFixedSize(cols * 20, rows * 20);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    setShowGrid(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);
    setMouseTracking(true);

    // Disable scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setStyleSheet("QTableWidget::item { border: none; }");
    verticalHeader()->setMinimumSectionSize(0);
    horizontalHeader()->setMinimumSectionSize(0);

    for (int i = 0; i < rows; ++i)
        setRowHeight(i, 10);
    for (int j = 0; j < cols; ++j)
        setColumnWidth(j, 10);
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
