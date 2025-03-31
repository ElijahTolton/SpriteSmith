#include "sprite.h"
#include "qevent.h"
#include "qjsonobject.h"
#include <QFile>
#include <QJsonDocument>

Sprite::Sprite(int canvasSize, int layerCount, QObject *parent)
    : QObject{parent}, layerCount(layerCount), canvasDimension(canvasSize)
{
    frames = new FrameModel(canvasSize, canvasSize);

    connect(frames, &FrameModel::nextFrame, this, &Sprite::sendFrame);
    connect(this, &Sprite::newFramerateSignal, frames, &FrameModel::updateFramerate);
}

void Sprite::save(){
    QJsonObject json = frames->toJSON();

    QJsonDocument doc(json);

    // Create File and load.
    QFile file("sprite.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void Sprite::load(QJsonObject json) {
    frames = new FrameModel(json);
}

void Sprite::sendFrame(Frame& frame) {

    QImage image = frame.getTopLayer().getImage();

    emit displayFrame(QPixmap::fromImage(image));
}

void Sprite::updateFramerate(int framerate) {
    emit newFramerateSignal(framerate);
}
