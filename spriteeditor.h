#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include "sprite.h"
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>

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


signals:
    void pixelCLicked(const QPoint& point);

public slots:
    void setColor(QColor color);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QColor currentColor = Qt::red;  // Default drawing color

    void changeCellColor(QMouseEvent *event);
    void calculateCanvasSizeAdjustment();
    void setCanvasContents(QImage image);
};

#endif // SPRITEEDITOR_H
