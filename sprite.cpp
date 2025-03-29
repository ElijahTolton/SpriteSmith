#include "sprite.h"
#include "qevent.h"
#include "qjsonobject.h"


Sprite::Sprite(int canvasSize, int layerCount, QObject *parent)
    : QObject{parent}, frames(canvasSize, canvasSize), layerCount(layerCount), canvasDimension(canvasSize)
{}

void Sprite::save(){
    // TODO Call FrameModel Json Create QJSONDocument
    QJsonObject placeholder;
    QJsonDocument doc;  // Create a QJsonDocument from the QJsonObject

    // Create File and load.
    QFile file("data.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void Sprite::load(QJsonObject json){
    frames = FrameModel(json);
}
