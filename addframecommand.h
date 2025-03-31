#ifndef ADDFRAMECOMMAND_H
#define ADDFRAMECOMMAND_H

#include <QUndoCommand>
#include <QJsonObject>
#include "framemodel.h"

/**
 * @brief Class that represents an edit to frame timeline
 *
 * @author Canon Curtis
 * @date March 30, 2025
 */
class AddFrameCommand : public QUndoCommand
{
public:
    /**
     * @brief Constructor for AddFrameCommand
     * @param frameModel - the timeline the frame was added to.
     * @param frameJSON - the JSON of the frame that was added to timeline.
     * @param frameIndex - the index of the frame that was added.
     */
    AddFrameCommand(FrameModel& frameModel, QJsonObject frameJSON, int frameIndex);

    /**
     * @brief Removes the added frame from the timeline.
     */
    void undo() override;

    /**
     * @brief Re-adds the frame to the timeline.
     */
    void redo() override;
private:
    // Timeline the frame was added to.
    FrameModel& frameModel;

    // JSON of the frame that was added.
    QJsonObject frameJSON;

    // The index of the frame that was added.
    int frameIndex;
};

#endif // ADDFRAMECOMMAND_H
