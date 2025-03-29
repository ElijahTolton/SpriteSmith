#include "sprite.h"
#include "qevent.h"
#include "qjsonobject.h"
#include <QFile>
#include <QJsonDocument>


Sprite::Sprite(int canvasSize, int layerCount, QObject *parent)
    : QObject{parent}, frames(canvasSize, canvasSize), layerCount(layerCount), canvasDimension(canvasSize)
{}

void Sprite::save(){
    QJsonObject json = frames.toJSON();

    QJsonDocument doc(json);

    // Create File and load.
    QFile file("sprite.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void Sprite::load(QJsonObject json){
    frames = FrameModel(json);
}
