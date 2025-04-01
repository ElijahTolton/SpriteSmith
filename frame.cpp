#include "frame.h"
#include "layermodel.h"

/**
 * @brief Class representing a single instance of an animation Frame
 *
 * @author Canon Curtis
 * @date March 29, 2025
 *
 * Checked by Canon Curtis
 */

Frame::Frame(int width, int height) : layers(width, height) {
}

Frame::Frame(int layerCount, int width, int height) : layers(width, height){
    for (int i = 0; i < layerCount - 1; i++) {
        layers.addLayer();
    }
}

Frame::Frame(const Frame& other)
    : layers(other.layers)  // Use the copy constructor of LayerModel directly
{

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

Layer& Frame::getTopLayer() {
    return layers.getTopLayer();
}

LayerModel& Frame::getLayerModel() {
    return layers;
}

QJsonObject Frame:: toJSON() const{
    return layers.ToJSON();
}

Frame::Frame(QJsonObject jsonInformation)
    : layers(jsonInformation)  // Initialize layers using the constructor of LayerModel that accepts QJsonObject
{
    frameIndex = 0;  // Initialize frameIndex after layers has been initialized
}

