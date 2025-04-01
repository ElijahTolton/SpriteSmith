#include "layermodel.h"
#include <QJsonObject>
#include <QJsonArray>

/**
 * @brief The LayerModel class contains the logic behind manipulating the layer class
 *
 * @author Dean Smith, Landon Huking, & Alex Lancaster (Documentation)
 * @date March 31, 2025
 *
 * Checked by Landon Huking
 */

LayerModel::LayerModel(int width, int height)
    : width(width), height(height) {
    layers.emplace_back(width, height);
    activeLayer = &layers.back();
}

LayerModel::LayerModel(const LayerModel& other)
    : width(other.width), height(other.height), activeLayer(nullptr) {
    // Copy the layers vector using the default vector copy constructor
    layers = other.layers;

    // Set the activeLayer pointer to the same layer as the other object
    if (!layers.empty()) {
        activeLayer = &layers.front();  // or you can copy the activeLayer logic as needed
    }
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

Layer& LayerModel::getTopLayer() {
    return getLayer(layers.size() - 1);
}

int LayerModel::getWidth() const {
    return width;
}

int LayerModel::getHeight() const {
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
                activeLayer = &layers.back();
            }
        }
    } catch(std::exception e) {
        // Handle the case where the "frames" key is missing or is not an array
        qWarning() << "Invalid or missing 'layers' array in JSON";
    }
}

void LayerModel::mirrorLayer() {
    layers[0].mirror();
    emit layerChanged();
}

void LayerModel::rotateLayer() {
    layers[0].rotate();
    emit layerChanged();
}



