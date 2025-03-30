#include "layermodel.h"
#include <algorithm>  // for std::find
#include "layermodel.h"
#include <QJsonObject>
#include <QJsonArray>


LayerModel::LayerModel(int width, int height)
    : width(width), height(height), activeLayer(&layers[0]) {
    layers.emplace_back(width, height);
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

void LayerModel::setActiveLayer(int index){
    if (index >= 0 && index < static_cast<int>(layers.size())) {
        layers[index].setActive(true);  // Set visibility to true
    }
}

int LayerModel::getWidth() {
    return width;
}

int LayerModel::getHeight() {
    return height;
}


void LayerModel::drawPixel(QColor color, int x, int y){
    activeLayer->drawPixel(color, x, y);
}

QJsonObject LayerModel::ToJSON() const {
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

LayerModel::LayerModel::LayerModel(QJsonObject json)
    : width(json["width"].toInt()), height(json["width"].toInt()), activeLayer(nullptr) // Set a default layer
    // Your constructor body
{
    try{
        width = json["width"].toInt();
        height = json["height"].toInt();

        // Ensure the JSON object has a "frames" key and it's an array
        QJsonArray layersArray = json["layers"].toArray();

        // Loop through each frame in the array and reconstruct each frame
        for (const QJsonValue &value : layersArray) {
            if (value.isObject()) {
                Layer layer(value.toObject());
                layers.push_back(layer);
                activeLayer = &layer;
            }
        }
    } catch(std::exception e) {
        // Handle the case where the "frames" key is missing or is not an array
        qWarning() << "Invalid or missing 'layers' array in JSON";
    }
}


