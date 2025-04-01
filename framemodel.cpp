#include "framemodel.h"
#include <QJsonArray>

/**
 * @brief Class representing a frame object for animation timeline.
 *
 * @authors Canon Curtis and Elijah Tolton
 * @date March 29, 2025
 */

FrameModel::FrameModel(int width, int height) : width{width}, height{height} {
    frames.push_back(Frame(width, height));
    timer = new QTimer;

    connect(timer, &QTimer::timeout, this, &FrameModel::sendNextFrame);
    timer->start();
}

void FrameModel::addFrame() {
    frames.push_back(Frame(width, height));
}

void FrameModel::duplicateFrame(Frame frame) {
    frames.push_back(frame);
}

void FrameModel::removeFrame(int frameIndex) {
    if (frameIndex >= 0 && frameIndex < static_cast<int>(frames.size())) {
        frames.erase(frames.begin() + frameIndex);  // Remove layer at index
    }
}

Frame& FrameModel::getFrame(int frameIndex) {
    if (frameIndex < 0 || frameIndex >= static_cast<int>(frames.size())) {
          throw std::out_of_range("Frame index out of range");
    }
    return frames.at(frameIndex);
}

std::vector<Frame>& FrameModel::getFrames() {
    return this->frames;
}

void FrameModel::updateFramerate(int framerate) {
    this->framerate = framerate;
    timer->setInterval(framerate);
}

void FrameModel::sendNextFrame() {
    if (nextFrameIndex > frames.size() - 1)
        nextFrameIndex = 0;

    emit nextFrame(getFrame(nextFrameIndex));
}

QJsonObject FrameModel::toJSON() {
    QJsonObject json;
    // Save canvas dimensions
    json["width"] = width;
    json["height"] = height;

    QJsonArray jsonArray;
    int numberFrames = frames.size();
    for (int i = 0; i < numberFrames; i++){
        jsonArray.append(frames[i].toJSON());
    }
    json.insert("frames", jsonArray);

    return json;
}


FrameModel::FrameModel(QJsonObject JSON){
    // Ensure the JSON object has a "frames" key and it's an array
    if (JSON.contains("frames") && JSON["frames"].isArray()) {
        QJsonArray framesArray = JSON["frames"].toArray();
        width = JSON["width"].toInt();
        height = JSON["height"].toInt();

        // Loop through each frame in the array and reconstruct each frame
        for (const QJsonValue &value : framesArray) {
            if (value.isObject()) {
                Frame frame(value.toObject());
                frames.push_back(frame);
            }
        }
    } else {
        // Handle the case where the "frames" key is missing or is not an array
        qWarning() << "Invalid or missing 'frames' array in JSON";
    }

    timer = new QTimer;
}
