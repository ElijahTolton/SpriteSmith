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
 *
 * @authors Elijah Tolton, Landon Huking, & Alex Lancaster (documentation)
 * @date March 31, 2025
 */
class Sprite : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the Sprite Class
     * @param canvasSize - Width and height of the drawing canvas
     * @param layerCount - The number of layers the Sprite contains
     * @param parent - The QObject parent of Sprite
     */
    Sprite(int canvasSize, int layerCount, QObject *parent = nullptr);

    /**
     * @brief Collection of all of the frames associated with a sprite
     */
    FrameModel* frames;

    /**
     * @brief Width and height of the canvas
     */
    int canvasDimension;

private:
    /**
     * @brief The number of layers across each frame
     */
    int layerCount;

    /**
     * @brief The current frame of the Sprite
     */
    int currentFrame = 0;

public slots:
    /**
     * @brief Saves all the infomation contained in Sprite
     */
    void save(QString fileName);

    /**
     * @brief Takes in a Json representation of the sprite that will be loaded into the model
     * @param The JSON representation to load into the model
     */
    void load(QString fileName);

    /**
     * @brief Listens when to send a frame to the animation preview
     * @param frame - frame from the top layer to display
     */
    void sendFrame(Frame& frame);

    /**
     * @brief Listens when to send a frame to the frame preview
     * @param Index of the frame to update the frame preview image
     */
    void sendFramePreview(int frameIndex);

    /**
     * @brief Listens when to update the framerate of the sprite
     * @param The new framerate
     */
    void updateFramerate(int framerate);

signals:
    /**
     * @brief Sends Json of this sprite to the view
     * @param The JSON representation of Sprite
     */
    void savedSprite(QString fileName);

    /**
     * @brief Displays the pixel that was clicked on
     * @param The color of the pixel which was clicked
     */
    void displayColor(QColor color);

    /**
     * @brief Displays frame in animation preview
     * @param pixmap - The frame image to be displayed
     */
    void displayFrame(QPixmap pixmap);

    void updateFrame(QPixmap pixmap);
    void newFramerateSignal(int framerate);

};

#endif // SPRITE_H
