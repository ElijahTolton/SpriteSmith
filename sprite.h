#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include "framemodel.h"
#include <QPixmap>
#include <QFile>

/**
 * @brief The Sprite represents all of the things
 * that are our sprite object. Contains all the Frames
 * which contain all of the Layers.
 */
class Sprite : public QObject
{
    Q_OBJECT
public:

    Sprite(int canvasSize, int layerCount, QObject *parent = nullptr);

    // This is a collection of all of the frames associated with this sprite.
    FrameModel* frames;

    // The width or height of the canvas
    int canvasDimension;
private:
    // The number of layers across each frame.
    int layerCount;

    int currentFrame = 0;

public slots:
    // Saves all of the info about this sprite and emits savedSprite.
    void save(QString fileName);

    // Takes in a Json represnetation of the sprite that will be loaded into the model.
    void load(QJsonObject JSON);

    void sendFrame(Frame& frame);

    void sendFramePreview(int frameIndex);

    void updateFramerate(int framerate);

signals:
    // Sends Json of this sprite to the view.
    void savedSprite(QString fileName);

    // Displays the pixel that was clicked on.
    void displayColor(QColor color);

    // Displays frame in animation preview
    void displayFrame(QPixmap pixmap);

    void updateFrame(QPixmap pixmap);

    void newFramerateSignal(int framerate);
};

#endif // SPRITE_H
