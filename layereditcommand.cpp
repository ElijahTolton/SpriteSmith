#include "layereditcommand.h"

/**
 * @brief Class represents any change to the sprite and allows these edits to be undone and redid.
 *
 * @author Canon Curtis
 * @date March 30, 2025
 *
 * Checked by Canon Curtis
 */
LayerEditCommand::LayerEditCommand(Layer& editedLayer, QJsonObject uneditedJSON, QJsonObject editedJSON) :
    uneditedJSON{uneditedJSON}, editedJSON{editedJSON}, editedLayer{editedLayer}
{
    setText("Sprite edited");
}

void LayerEditCommand::undo() {
    editedLayer.setFromJSON(uneditedJSON);
}

void LayerEditCommand::redo() {
    editedLayer.setFromJSON(editedJSON);
}
