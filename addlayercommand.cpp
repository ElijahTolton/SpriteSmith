#include "addlayercommand.h"

/**
 * @brief Class that represents an edit to the layer model.
 *
 * @author Canon Curtis
 * @date March 30, 2025
 *
 * Checked by Canon Curtis
 */

AddLayerCommand::AddLayerCommand(LayerModel& layerModel, QJsonObject layerJSON, int layerIndex) :
    layerModel{layerModel}, layerJSON{layerJSON}, layerIndex{layerIndex}
{
    setText("Layer Added");
}

void AddLayerCommand::undo() {
    layerModel.removeLayer(layerIndex);
}

void AddLayerCommand::redo() {
    layerModel.duplicateLayer(Layer(layerJSON));
}
