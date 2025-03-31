#include "frame.h"
#include "layermodel.h"

Frame::Frame(int width, int height) : layers(width, height) {
}

Frame::Frame(int layerCount, int width, int height) : layers(width, height){
    for (int i = 0; i < layerCount - 1; i++) {
        layers.addLayer();
    }
}

Frame::Frame(const Frame& other) : layers(0, 0) {
    for(const Layer& layer : other.layers.getLayers()) {
        layers.duplicateLayer(layer);
    }
}

Frame::~Frame() {
}

Frame& Frame::operator=(const Frame& other) {
    for(const Layer& layer : other.layers.getLayers()) {
        layers.duplicateLayer(layer);
    }

    return *this;
}

void Frame::addLayer() {
    layers.addLayer();
}

void Frame::addLayer(const Layer& layer) {
    layers.duplicateLayer(layer);
}

void Frame::removeLayer(int layerIndex) {
    layers.removeLayer(layerIndex);
}

Layer& Frame::getActiveLayer() {
    return layers.getActiveLayer();
}

QJsonObject Frame:: toJSON() const{
    return layers.ToJSON();
}

Frame::Frame(QJsonObject jsonInformation)
    : layers(jsonInformation)  // Initialize layers using the constructor of LayerModel that accepts QJsonObject
{
    frameIndex = 0;  // Initialize frameIndex after layers has been initialized
}

