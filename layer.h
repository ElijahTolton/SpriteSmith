#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QJsonObject>

class Layer
{
public:
    Layer() = delete;
    Layer(int width, int height);
    Layer(Layer const &layer);
    Layer& operator=(const Layer &other);

    bool isActive() const;
    QImage& getImage();

    void setShown(bool active);
    void setActive(bool active);

    void mirror();
    void rotate();

    int getWidth() const;
    int getHeight() const;

    void setImage(const QImage& newImage);
    bool operator==(const Layer &layer) const;

    QJsonObject toJSON() const;

    void drawPixel(QColor color, int x, int y);

    Layer(QJsonObject);

private:
    QImage image;
    bool active;
    int width;
    int height;
};

#endif // LAYER_H
