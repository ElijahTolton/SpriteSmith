#include "tool.h"

/**
 * @brief Handles all tool actions from MainWindow class
 *
 * @authors Landon Huking & Alex Lancaster (documentation)
 * @date March 27, 2025
 */

Tool::Tool(SpriteEditor* canvas, LayerModel* layers)
    : canvas(canvas), layers(layers)
{
    connect(canvas, &SpriteEditor::pixelCLicked, this, &Tool::setPixelPos);
    connect(this, &Tool::editSignal, layers, &LayerModel::drawPixel);
}

void Tool::onEdit() {
    emit editSignal(color, x, y);
    emit repaintSignal();
}

void Tool::onMirror() {
    emit mirrorSignal();
}

void Tool::onRotate() {
    emit rotateSignal();
}

void Tool::setPixelPos(const QPoint& point) {
    x = point.x();
    y = point.y();
}

void Tool::setColor(QColor color) {
    this->color = color;
    canvas->setColor(color);
}

void Tool::setErase() {
    this->color = QColor(0,0,0,0);
    canvas->setColor(QColor(0,0,0,0));
}

Tool::~Tool() { }
