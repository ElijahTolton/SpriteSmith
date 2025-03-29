#include "frame.h"

Frame::Frame(int width, int height) : layers(width, height) {
}

Frame::Frame(int layerCount, int width, int height) : layers(width, height){
    for (int i = 0; i < layerCount - 1; i++) {
        layers.addLayer();
    }
}

Frame::Frame(Frame& other) : layers(0, 0) {
    for(const Layer& layer : other.layers.getLayers()) {
        layers.duplicateLayer(layer);
    }
}

Frame::~Frame() {
}

Frame& Frame::operator=(Frame& other) {
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
