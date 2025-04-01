#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <vector>
#include "frame.h"
#include <QTimer>

/**
 * @brief Class representing a frame object for animation timeline.
 *
 * @authors Canon Curtis, Elijah Tolton & Alex Lancaster (documentation)
 * @date March 29, 2025
 */
class FrameModel : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief Container for all frames in sprite
     */
    std::vector<Frame> frames;

    /**
     * @brief timer to update frames in animation preview
     */
    QTimer* timer;

    /**
     * @brief Framerate/Time for preview to send information
     */
    int framerate = 0;

    /**
     * @brief nextFrameIndex contains the next frame to be displayed
     * in the animation preview
     */
    uint nextFrameIndex = 0;

    /**
     * @brief width of frame canvas
     */
    int width;

    /**
     * @brief height of frame canvas
     */
    int height;

public:
    /**
     * @brief Constructs model with empty frame.
     * @param width - the width of each layer in the frames
     * @param height - the height of each layer in the frames
     */
    FrameModel(int width, int height);

    /**
     * @brief Constructor that deserializes JSON and reconstructs model
     * @param JSON - JSON containing information on how to reconstruct model.
     */
    FrameModel(QJsonObject JSON);

signals:
    /**
     * @brief nextFrame to be displayed in the animation preview
     * @param frame payload to be displayed
     */
    void nextFrame(Frame& frame);

public slots:
    /**
     * @brief Adds a frame to the model
     */
    void addFrame();

    /**
     * @brief Copies given frame to the model
     * @param frame - The frame to be copied
     */
    void duplicateFrame(Frame frame);

    /**
     * @brief Removes frame at given index from model.
     * @param frameIndex - the index to remove the frame from.
     */
    void removeFrame(int frameIndex);

    /**
     * @brief Returns frame reference at index.
     * @param frameIndex - index Frame is located at.
     * @return Reference to frame at that index.
     */
    Frame& getFrame(int frameIndex);

    /**
     * @brief Returns reference to vector containing all frames in sprite.
     * @return Reference to vector containing frames.
     */
    std::vector<Frame>& getFrames();

    /**
     * @brief Updates framerate member and framerate of timer
     * @param framerate - new animation framerate
     */
    void updateFramerate(int framerate);

    /**
     * @brief Slot timer calls to send next frame
     */
    void sendNextFrame();

    /**
     * @brief Returns JSON representation of FrameModel.
     * @return JSON representation of model.
     */
    QJsonObject toJSON();
};

#endif // FRAMEMODEL_H
