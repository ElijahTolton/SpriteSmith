#include "framemodel.h"
#include <QJsonArray>

FrameModel::FrameModel(int width, int height) : width{width}, height{height} {
    frames.push_back(Frame(width, height));
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

QJsonObject FrameModel::toJSON(){
    QJsonObject json;
    QJsonArray jsonArray;
    int numberFrames = frames.size();

    for( int i = 0; i < numberFrames; i++){
        jsonArray.append(frames[i].toJSON());
    }

    json.insert("frames", jsonArray);

    return json;
}

FrameModel::FrameModel(QJsonObject JSON){
    //TODO create from Json
    JSON.insert("", "hello");
}
