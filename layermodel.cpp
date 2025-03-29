#include "layermodel.h"
#include <algorithm>  // for std::find
#include "layermodel.h"
#include <QJsonObject>
#include <QJsonArray>


LayerModel::LayerModel(int width, int height) : width(width), height(height) {
    layers.push_back(Layer(width, height));  // Initialize with one layer
}

void LayerModel::addLayer() {
    layers.push_back(Layer(width, height));  // Adds new blank layer
}

void LayerModel::duplicateLayer(const Layer& layer) {
    layers.push_back(layer);  // Pushes a copy of the existing layer
}

void LayerModel::removeLayer(int layerIndex) {
    if (layerIndex >= 0 && layerIndex < static_cast<int>(layers.size())) {
        layers.erase(layers.begin() + layerIndex);  // Remove layer at index
    }
}

std::vector<Layer> LayerModel::reorderLayer(const Layer& layer, int newPosition) {
    auto it = std::find(layers.begin(), layers.end(), layer);  // Find layer
    if (it == layers.end()) return layers;  // If layer not found, return unchanged list

    Layer temp = *it;  // Copy the layer
    layers.erase(it);  // Remove it from the current position

    newPosition = std::max(0, std::min(newPosition, static_cast<int>(layers.size())));  // Clamp position
    layers.insert(layers.begin() + newPosition, temp);  // Insert at new position

    return layers;  // Return updated vector
}

void LayerModel::hideLayer(int layerIndex) {
    if (layerIndex >= 0 && layerIndex < static_cast<int>(layers.size())) {
        layers[layerIndex].setShown(false);  // Assuming Layer has `setShown(bool)`
    }
}

void LayerModel::showLayer(int layerIndex) {
    if (layerIndex >= 0 && layerIndex < static_cast<int>(layers.size())) {
        layers[layerIndex].setShown(true);  // Set visibility to true
    }
}

Layer& LayerModel::getLayer(int layerIndex) {
    if (layerIndex < 0 || layerIndex >= static_cast<int>(layers.size())) {
        throw std::out_of_range("Layer index out of range");
    }
    return layers[layerIndex];
}

const std::vector<Layer>& LayerModel::getLayers() const {
    return layers;  // Return reference to layers vector
}

int LayerModel::getWidth() {
    return width;
}

int LayerModel::getHeight() {
    return height;
}


QJsonObject LayerModel::toJSON() const {
    QJsonObject jsonObj;

    // Add width and height to the JSON object
    jsonObj["width"] = width;
    jsonObj["height"] = height;

    // Create a JSON array to store all layers
    QJsonArray layersArray;

    // Iterate through each layer and convert it to JSON
    for (const auto& layer : layers) {
        layersArray.append(layer.toJSON());
    }

    // Add the layers array to the JSON object
    jsonObj["layers"] = layersArray;

    return jsonObj;
}

