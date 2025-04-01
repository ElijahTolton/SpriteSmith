#include "sprite.h"
#include "qevent.h"
#include <QJsonDocument>

Sprite::Sprite(int canvasSize, int layerCount, QObject *parent)
    : QObject{parent}, layerCount(layerCount), canvasDimension(canvasSize)
{
    frames = new FrameModel(canvasSize, canvasSize);

    connect(frames, &FrameModel::nextFrame, this, &Sprite::sendFrame);
    connect(this, &Sprite::newFramerateSignal, frames, &FrameModel::updateFramerate);
}

void Sprite::save(QString fileName){
    QJsonObject json = frames->toJSON();

    QJsonDocument doc(json);

    // Create File and load.
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        qDebug() << "Saved file: " << fileName;
    }
}

void Sprite::load(QString fileName) {

    QByteArray fileData;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileData = file.readAll();
        file.close();
    } else {
        qDebug() << "Loading sprite porject file " << fileName << " failed";
    }

    // Parse JSON data
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qDebug() << "Invalid JSON file!";
        return;
    }

    // Convert to QJsonObject
    QJsonObject jsonObj = jsonDoc.object();

    frames = new FrameModel(jsonObj);
}

void Sprite::sendFrame(Frame& frame) {
    QImage image  = frame.getTopLayer().getImage();
    emit displayFrame(QPixmap::fromImage(image));
}

void Sprite::sendFramePreview(int frameIndex) {
    QImage image = frames->getFrame(frameIndex).getTopLayer().getImage();

    emit updateFrame(QPixmap::fromImage(image));
}

void Sprite::updateFramerate(int framerate) {
    emit newFramerateSignal(framerate);
}
