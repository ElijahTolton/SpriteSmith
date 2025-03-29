/**
 * @brief
 * Header file for Tool model class that handles all
 * tool actions from MainWindow class
 *
 * @authors
 * Landon Huking
 *
 * @date
 * Created:         3/25/25
 * Last modified:   3/27/25
 */

#ifndef TOOL_H
#define TOOL_H

#include <QMainWindow>
#include <QString>
#include <QColor>
#include <layermodel.h>
#include <spriteeditor.h>

class Tool : QWidget
{
public:
    Tool(SpriteEditor* canvas, LayerModel* activeLayer);
    ~Tool();

private:
    QColor color;
    SpriteEditor* canvas;
    LayerModel* activeLayer;
    int x, y;

signals:
    void editSignal(QColor color, int x, int y);
    void rotateSignal();
    void mirrorSignal();

public slots:
    void onEdit(QColor color, int x, int y);
    void onMirror();
    void onRotate();
    void setPixelPos(const QPoint& point);
};

#endif // TOOL_H
