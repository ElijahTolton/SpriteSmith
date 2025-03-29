/**
 * @brief
 * Implementation file for Tool model class that handles all
 * tool actions from MainWindow class
 *
 * @authors
 * Landon Huking
 *
 * @date
 * Created:         3/25/25
 * Last modified:   3/27/25
 */

#include "tool.h"

Tool::Tool(SpriteEditor* canvas, LayerModel* activeLayer) {
    connect(canvas, &SpriteEditor::pixelCLicked, this, &Tool::setPixelPos);
}


void Tool::onEdit(QColor color, int x, int y) {
    emit editSignal(color, x, y);
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

Tool::~Tool() { }
