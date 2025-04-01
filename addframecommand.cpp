#include "addframecommand.h"

/**
 * @brief Class that represents an edit to frame timeline
 *
 * @author Canon Curtis
 * @date March 30, 2025
 *
 * Checked by Canon Curtis
 */

AddFrameCommand::AddFrameCommand(FrameModel& frameModel, QJsonObject frameJSON, int frameIndex) :
    frameModel{frameModel}, frameJSON{frameJSON}, frameIndex{frameIndex}
{
    setText("Frame added");
}

void AddFrameCommand::undo() {
    frameModel.removeFrame(frameIndex);
}

void AddFrameCommand::redo() {
    frameModel.duplicateFrame(Frame(frameJSON));
}
