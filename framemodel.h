#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <vector>
#include<QJsonObject>

/**
 * @brief Class representing a frame object for animation timeline.
 *
 * @author Canon Curtis
 * @date March 29, 2025
 */
class FrameModel
{
private:
    //Vector of layers contained by frame.
    std::vector<int> layers;
public:
    /**
     * @brief Constructor to create instance of model for Frame.
     */
    FrameModel();

    /**
     * @brief Constructor for FrameModel that initializes with number of empty layers.
     * @param layerCount - the number of empty layers to intialize vector with.
     */
    FrameModel(int layerCount);

    /**
     * @brief Copy constructor for FrameModel.
     * @param other - Frame model to copy from.
     */
    FrameModel(const FrameModel& other);

    /**
     * @brief Deletes given layer inside frame vector at index.
     * @param layerIndex - The index of the layer to be deleted.
     */
    void deleteLayer(int layerIndex);

    /**
     * @brief Overridden = operator to copy information into this object.
     * @param other - the frame to be copied into this model.
     * @return Reference to the modified FrameModel Instance.
     */
    FrameModel& operator=(const FrameModel& other);

    /**
     * @brief Converts current instance into Json Object.
     * @return QJsonObject representation of the model.
     */
    QJsonObject toJson();
};

#endif // FRAMEMODEL_H
