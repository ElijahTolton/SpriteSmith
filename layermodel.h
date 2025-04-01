#ifndef LAYERMODEL_H
#define LAYERMODEL_H

#include "layer.h"

/**
 * @brief The LayerModel class contains the logic behind manipulating the layer class
 *
 * @author Dean Smith, Landon Huking, & Alex Lancaster (Documentation)
 * @date
 */
class LayerModel : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new LayerModel with one layer
     * @param width - The width of the initial layer
     * @param height - The height of the initial layer
     */
    LayerModel(int width, int height);

    /**
     * @brief Copy Constructor for LayerModel
     * @param other - Layer to be copied
     */
    LayerModel(const LayerModel& other);

    /**
     * @brief Adds a new blank layer
     */
    void addLayer();

    /**
     * @brief Creates a new layer that is the duplicate of another layer
     * @param layer - Layer used for duplication
     */
    void duplicateLayer(const Layer& layer);

    /**
     * @brief Removes a layer at a given index
     * @param layerIndex - Index of layer to be removed (0 = bottom)
     */
    void removeLayer(int layerIndex);

    /**
     * @brief Gives a reference to the requested layer
     * @param layerIndex - Index of desired layer
     * @return A Layer at the layerIndex
     */
    Layer& getLayer(int layerIndex);

    /**
     * @brief Gives the full vector of layers in the LayerModel
     * @return A vector of all Layers
     */
    const std::vector<Layer>& getLayers() const;

    /**
     * @brief Gets the width
     * @return The width of the layer
     */
    int getWidth() const;

    /**
     * @brief Gets the height
     * @return  The height of the layer
     */
    int getHeight() const;

    /**
     * @brief Draws a pixel in the active layer
     * @param color - Color of the pixel to draw
     * @param x - X position in the canvas
     * @param y - Y position in the canvas
     */
    void drawPixel(QColor color, int x, int y);

    /**
     * @brief Activates the given layer
     * @param layer - Index of the layer to activate
     */
    void setActiveLayer(int layer);

    /**
     * @brief Gets the top (highest index) layer
     * @return returns the active layer
     */
    Layer& getTopLayer();

    /**
     * @brief Vector containing all layers in the LayerModel
     */
    std::vector<Layer> layers;

    /**
     * @brief JSON Serializer
     * @return A QJsonObject representation of all layers
     */
    QJsonObject ToJSON() const;

    /**
     * @brief Deserializer for LayerModel
     * @param QJsonObject json representation of Layers
     */
    LayerModel(QJsonObject json);

public slots:
    /**
     * @brief Mirrors the first layer
     */
    void mirrorLayer();

    /**
     * @brief Rotates the first layer
     */
    void rotateLayer();

signals:
    /**
     * @brief Emits when a layer has been changed (mirrored or rotated)
     */
    void layerChanged();

private:
    /**
     * @brief width of the layer
     */
    int width;

    /**
     * @brief height of the layer
     */
    int height;

    /**
     * @brief The current active layer
     */
    Layer* activeLayer;
};

#endif // LAYERMODEL_H
