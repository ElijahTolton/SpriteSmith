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
     * @brief SpriteEditor
     * @param parent
     */
    explicit SpriteEditor(QWidget *parent = nullptr);

    /**
     * @brief setCanvasSize
     */
    void setCanvasSize();

    /**
     * @brief repaint
     */
    void repaint();

    /**
     * @brief mirrorLayer
     */
    void mirrorLayer();

    /**
     * @brief setSprite
     * @param sprite
     */
    void setSprite(Sprite *sprite);

    /**
     * @brief undo
     */
    void undo();

    /**
     * @brief redo
     */
    void redo();

signals:
    /**
     * @brief pixelCLicked
     * @param point
     */
    void pixelCLicked(const QPoint& point);

    /**
     * @brief updatePreviews
     */
    void updatePreviews();

public slots:
    /**
     * @brief setColor
     * @param color
     */
    void setColor(QColor color);

protected:
    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief mouseMoveEvent
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    /**
     * @brief currentColor
     */
    QColor currentColor = Qt::red;  // Default drawing color

    /**
     * @brief uneditedJSON
     */
    QJsonObject uneditedJSON; // Unedited JSON of layer that was edited

    /**
     * @brief undoStack
     */
    QUndoStack undoStack; // Stack of undo commands

    /**
     * @brief changeCellColor
     * @param event
     */
    void changeCellColor(QMouseEvent *event);

    /**
     * @brief calculateCanvasSizeAdjustment
     */
    void calculateCanvasSizeAdjustment();

    /**
     * @brief setCanvasContents
     * @param image
     */
    void setCanvasContents(QImage image);
};

#endif // SPRITEEDITOR_H
