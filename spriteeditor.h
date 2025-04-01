#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include "sprite.h"
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>
#include <QJsonObject>
#include <QUndoStack>

class QHeaderView;


/**
 * @brief The SpriteEditor class manages the pixel editing interface
 *
 * SpriteEditor is responsible for rendering a grid-based pixel canvas, handling user input,
 * and facilitating editing operations such as painting, mirroring, undoing, and redoing changes
 *
 * @authors Dean Smith, Alex Lancaster, Canon Curtis, & Landon Huking
 * @date March 31, 2025
 */
class SpriteEditor : public QTableWidget {
    Q_OBJECT

public:
    /**
     * @brief Sprite instance that stores drawing
     */
    Sprite *sprite;

    /**
     * @brief Constructor for SpriteEditor
     * @param parent QWidget
     */
    explicit SpriteEditor(QWidget *parent = nullptr);

    /**
     * @brief Sets the size of the canvas.
     */
    void setCanvasSize();

    /**
     * @brief Redraws the canvas.
     *
     * Refreshes the display of the sprite editor to reflect the current pixel state.
     */
    void repaint();

    /**
     * @brief Mirrors the current layer horizontally.
     */
    void mirrorLayer();

    /**
     * @brief Sets the sprite object being edited
     *
     * Initializes the editor with the provided sprite, adjusting the grid dimensions accordingly.
     * @param sprite - The sprite to edit
     */
    void setSprite(Sprite *sprite);

    /**
     * @brief Undoes the last action.
     */
    void undo();

    /**
     * @brief Redoes the last undone action.
     */
    void redo();

signals:
    /**
     * @brief Emitted when a pixel is clicked
     * @param The position of the clicked pixel
     */
    void pixelCLicked(const QPoint& point);

    /**
     * @brief Emitted when the sprite editor updates, triggering preview refreshes
     */
    void updatePreviews();

public slots:
    /**
     * @brief Sets the current color selected
     * @param The new color to use for drawing pixels
     */
    void setColor(QColor color);

protected:
    /**
     * @brief Handles mouse press events for drawing pixels
     * @param The mouse event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse movement events for continuous drawing
     * @param The mouse event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse release events to finalize drawing actions
     * @param The mouse event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    /**
     * @brief The currently selected drawing color
     */
    QColor currentColor = Qt::red;  // Default drawing color

    /**
     * @brief Stores the JSON state of the layer before an edit for undo functionality
     */
    QJsonObject uneditedJSON; // Unedited JSON of layer that was edited

    /**
     * @brief Stack for undo and redo operations
     */
    QUndoStack undoStack; // Stack of undo commands

    /**
     * @brief Changes the color of a cell at the given mouse event position
     * @param The mouse event
     */
    void changeCellColor(QMouseEvent *event);

    /**
     * @brief Adjusts the canvas size to maintain a consistent pixel grid
     */
    void calculateCanvasSizeAdjustment();

    /**
     * @brief Sets the displayed contents of the canvas
     * @param The image to apply to the grid
     */
    void setCanvasContents(QImage image);
};

#endif // SPRITEEDITOR_H
