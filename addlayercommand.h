#ifndef ADDLAYERCOMMAND_H
#define ADDLAYERCOMMAND_H

#include <QUndoCommand>
#include <layermodel.h>

/**
 * @brief Class that represents an edit to the layer model.
 *
 * @author Canon Curtis
 * @date March 30, 2025
 */
class AddLayerCommand : public QUndoCommand
{
public:

    /**
     * @brief Constructor for AddLayerCommand
     * @param layerModel - the collection of layers where the layer was added.
     * @param layerJSON - the JSON of the layer that was added.
     * @param layerIndex - the index in the model where the layer was added.
     */
    AddLayerCommand(LayerModel& layerModel, QJsonObject layerJSON, int layerIndex);

    /**
     * @brief Removes the added layer from the sprite.
     */
    void undo() override;

    /**
     * @brief Re-adds the layer to the sprite.
     */
    void redo() override;
private:
    // Model the layer was added to.
    LayerModel& layerModel;

    // JSON of the layer that was added.
    QJsonObject layerJSON;

    // The index of the layer that was added.
    int layerIndex;
};

#endif // ADDLAYERCOMMAND_H
