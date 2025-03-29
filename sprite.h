#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>

/**
 * @brief The Sprite represents all of the things
 * that are our sprite object. Contains all the Frames
 * which contain all of the Layers.
 */
class Sprite : public QObject
{
    Q_OBJECT
public:
    explicit Sprite(QObject *parent = nullptr);

    Sprite(int canvasSize, int layerCount, QObject *parent = nullptr);

private:
    // This is a collection of all of the frames associated with this sprite.
    FrameModel frames;

    // The number of layers across each frame.
    int layerCount;

    // The width or height of the canvas
    int canvasDimension;

public slots:
    // Saves all of the info about this sprite and emits savedSprite.
    void save();

    // Takes in a Json represnetation of the sprite that will be loaded into the model.
    void load(QJsonDocument);

signals:
    // Sends Json of this sprite to the view.
    void savedSprite(QJsonDocument);

    // Displays the pixel that was clicked on.
    void displayColor(QColor);
};

#endif // SPRITE_H
