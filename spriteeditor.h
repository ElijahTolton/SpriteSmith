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
    explicit SpriteEditor(int rows, int cols, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QColor currentColor = Qt::red;  // Default drawing color
    void changeCellColor(QMouseEvent *event);
};

#endif // SPRITEEDITOR_H
