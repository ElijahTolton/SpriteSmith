#ifndef TOOL_H
#define TOOL_H

#include <QMainWindow>
#include <QString>
#include <QColor>
#include <layermodel.h>
#include <spriteeditor.h>
#include <frameview.h>

/**
 * @brief Handles all tool actions from MainWindow class
 *
 * @authors Landon Huking & Alex Lancaster (documentation)
 * @date March 27, 2025
 */
class Tool : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor for Tool
     */
    Tool() {};

    /**
     * @brief Constructs a Tool object with a reference to the canvas and layer model
     * @param canvas - Pointer to the SpriteEditor instance managing the drawing area
     * @param layers - Pointer to the LayerModel instance managing the layers
     */
    Tool(SpriteEditor* canvas, LayerModel* layers);

    /**
     * @brief Destructor for Tool
     */
    ~Tool();

private:
    /**
     * @brief The current color selected for drawing
     */
    QColor color;

    /**
     * @brief Pointer to the canvas (SpriteEditor) where drawing occurs
     */
    SpriteEditor* canvas;

    /**
     * @brief Pointer to the layer model managing different drawing layers
     */
    LayerModel* layers;

    /**
     * @brief The current x and y coordinates of the selected pixel
     */
    int x, y;

signals:
    /**
     * @brief Signal emitted when a pixel is edited.
     * @param color - The color applied to the pixel.
     * @param x - The x-coordinate of the pixel.
     * @param y - The y-coordinate of the pixel.
     */
    void editSignal(QColor color, int x, int y);

    /**
     * @brief Signal emitted to trigger a repaint of the canvas.
     */
    void repaintSignal();

    /**
     * @brief Signal emitted to rotate the current selection or layer.
     */
    void rotateSignal();

    /**
     * @brief Signal emitted to mirror the current selection or layer.
     */
    void mirrorSignal();

public slots:
    /**
     * @brief Handles the edit action by emitting an edit signal and requesting a repaint
     */
    void onEdit();

    /**
     * @brief Handles the mirror action by emitting a mirror signal
     */
    void onMirror();

    /**
     * @brief Handles the rotate action by emitting a rotate signal
     */
    void onRotate();

    /**
     * @brief  Sets the current pixel position
     * @param point - The QPoint containing the x and y coordinates
     */
    void setPixelPos(const QPoint& point);

    /**
     * @brief Sets the current drawing color
     * @param color - The QColor value to set as the active color
     */
    void setColor(QColor color);

    /**
     * @brief Enables the eraser by setting the color to transparent
     */
    void setErase();
};

#endif // TOOL_H
