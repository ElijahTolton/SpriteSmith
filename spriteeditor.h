#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>

class QHeaderView;

class SpriteEditor : public QTableWidget {
    Q_OBJECT

public:
    explicit SpriteEditor(QWidget *parent = nullptr);
    void setCanvasSize();

signals:
    void pixelCLicked(const QPoint& point);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QColor currentColor = Qt::red;  // Default drawing color
    void setColor(QColor color);
    void changeCellColor(QMouseEvent *event);
    void calculateCanvasSizeAdjustment();
};

#endif // SPRITEEDITOR_H
