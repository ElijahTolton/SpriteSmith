#ifndef LAYEREDITCOMMAND_H
#define LAYEREDITCOMMAND_H

#include <QUndoCommand>
#include <QJsonObject>
#include "layer.h"

/**
 * @brief Class represents any change to the sprite and allows these edits to be undone and redid.
 *
 * @author Canon Curtis
 * @date March 30, 2025
 */
class LayerEditCommand : public QUndoCommand
{
public:
    /**
     * @brief Constructor for LayerEditCommand
     * @param editedLayer - Reference to the layer was the edit was applied to.
     * @param uneditedJSON - the JSON of the layer before the edit was made.
     * @param editedJSON - the JSON of the layer after the edit was made.
     */
    LayerEditCommand(Layer& editedLayer, QJsonObject uneditedJSON, QJsonObject editedJSON);

    /**
     * @brief Undo command will set the current layer to the unedited JSON.
     */
    void undo() override;

    /**
     * @brief Redo command will set the current layer to the edited JSON.
     */
    void redo() override;
private:
    // JSONs of layer changes
    QJsonObject uneditedJSON;
    QJsonObject editedJSON;

    //The layer the edit was applied to
    Layer& editedLayer;
};

#endif // LAYEREDITCOMMAND_H
