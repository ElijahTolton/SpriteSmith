#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include "sprite.h"
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>
#include <QJsonObject>
#include <QUndoStack>

class QHeaderView;

class SpriteEditor : public QTableWidget {
    Q_OBJECT

public:
    Sprite *sprite;
    explicit SpriteEditor(QWidget *parent = nullptr);
    void setCanvasSize();
    void repaint();
    void mirrorLayer();
    void setSprite(Sprite *sprite);
    void undo();
    void redo();


signals:
    void pixelCLicked(const QPoint& point);
    void updatePreviews();

public slots:
    void setColor(QColor color);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QColor currentColor = Qt::red;  // Default drawing color

    QJsonObject uneditedJSON; // Unedited JSON of layer that was edited
    QUndoStack undoStack; // Stack of undo commands

    void changeCellColor(QMouseEvent *event);
    void calculateCanvasSizeAdjustment();
    void setCanvasContents(QImage image);
};

#endif // SPRITEEDITOR_H
