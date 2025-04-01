#ifndef FRAME_H
#define FRAME_H

#include "layermodel.h"
#include "layer.h"
#include <QJsonObject>

/**
 * @brief Class representing a single instance of an animation Frame
 *
 * @author Canon Curtis & Alex Lancaster (documentation)
 * @date March 29, 2025
 */
class Frame
{
private:
    /**
     * @brief Place frame is located in animation timeline
     */
    int frameIndex;
public:
    /**
     * @brief Container for all layers in a frame
     */
    LayerModel layers;

    /**
     * @brief Constructs Frame with 1 empty layer
     * @param width - width of layer
     * @param height - height of layer
     */
    Frame(int width, int height);

    /**
     * @brief Constructs Frame with given number empty layers
     * @param layerCount - number of empty layers to add
     * @param width - width of layers
     * @param height - height of layers
     */
    Frame(int layerCount, int width, int height);

    /**
     * @brief Copy constructor for Frame
     * @param other - the frame to copy information from
     */
    Frame(const Frame& other);

    /**
     * @brief Frame
     * @param jsonInformation
     */
    Frame(QJsonObject jsonInformation);

    /**
     * @brief Destructor for Frame
     */
    ~Frame();

    /**
     * @brief Operator overload to copy information from another frame
     * @param other - the other frame to copy information from
     * @return Reference to modified frame.
     */
    Frame& operator=(const Frame& other);

    /**
     * @brief Adds an empty layer to the LayerModel
     */
    void addLayer();

    /**
     * @brief Adds specified layer to Layer Model
     * @param layer - Layer to add to Model
     */
    void addLayer(const Layer& layer);

    /**
     * @brief Gets layer that is shown
     * @return the layer to be displayed
     */
    Layer& getTopLayer();

    /**
     * @brief Removes layer at given index from model
     * @param layerIndex - index to which layer to delete is located.
     */
    void removeLayer(int layerIndex);

    /**
     * @brief Creates a Json representation of the frame and its subsequent layers.
     * @return QJsonObject containing Json information to reconstruct Frame.
     */
    QJsonObject toJSON() const;
};

#endif // FRAME_H
