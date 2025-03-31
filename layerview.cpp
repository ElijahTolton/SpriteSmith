#include "layerview.h"

LayerView::LayerView(QWidget *parent) : QWidget(parent), layerIndex(0) {}

LayerView::LayerView(int index, QWidget *parent) : QWidget(parent), layerIndex(index) {}

void LayerView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setStyleSheet("background-color: #555555;");
    }
}

void LayerView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Restore original background color
        this->setStyleSheet("background-color: #3A3A3A;");
    }

    emit getLayerIndex(layerIndex);
    qDebug() << layerIndex;
}

void LayerView::removeLayer() {
    emit removeLayerIndex(layerIndex);
    qDebug() << layerIndex;
}
