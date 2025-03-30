#ifndef LAYERMODEL_H
#define LAYERMODEL_H
#include "layer.h"

class LayerModel : public QObject
{
public:
    // Creates a new LayerModel with one layer.
    LayerModel(int width, int height);

    // Adds a new blank layer
    void addLayer();

    // Creates a new layer that is the duplicate of another layer
    void duplicateLayer(const Layer& layer);

    // Given a layer index (0 = bottom), remove that layer
    void removeLayer(int layerIndex);

    // Given a layer and a new position, move that layer to be in a new position and return the new vector of layers
    std::vector<Layer> reorderLayer(const Layer& layer, int newPosition);

    // Hides the layer at the given index
    void hideLayer(int layerIndex);

    // Shows the layer at the given index
    void showLayer(int layerIndex);

    // Gives a reference to the requested layer
    Layer& getLayer(int layerIndex);

    // Gives the full vector of layers in the LayerModel
    const std::vector<Layer>& getLayers() const;

    // Get the width
    int getWidth();

    // Get the height
    int getHeight();

    //draws a pixel in the active layer
    void drawPixel(QColor color, int x, int y);

    //activates the given layer
    void setActiveLayer(int layer);

    // Vector containing all layers in the LayerModel
    std::vector<Layer> layers;

    // JSON Serializer
    QJsonObject ToJSON() const;

    LayerModel(QJsonObject json);

private:

    int width;
    int height;
    Layer* activeLayer;
};

#endif // LAYERMODEL_H
