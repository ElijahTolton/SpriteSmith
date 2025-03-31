#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include <QWidget>
#include <QMouseEvent>

class LayerView : public QWidget
{
    Q_OBJECT

public:
    // initilize the first layer to 0
    explicit LayerView(QWidget *parent = nullptr);
    explicit LayerView(int index, QWidget *parent = nullptr);

private:
    int layerIndex;

signals:
    void getLayerIndex(int layerIndex);
    void removeLayerIndex(int layerIndex);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void removeLayer();
};

#endif // LAYERVIEW_H
