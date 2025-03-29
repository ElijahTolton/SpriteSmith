/**
 * @brief
 * Implementation file for Tool model class that handles all
 * tool actions from MainWindow class
 *
 * @authors
 * Landon Huking
 *
 * @date
 * Created:         3/25/25
 * Last modified:   3/27/25
 */

#include "tool.h"

Tool::Tool(QMainWindow* window, Layer* activeLayer) : window(window), activeLayer(activeLayer) {

    //TO DO: Add connections between window signals and tool slots

    //TO DO: Add connections between tool slots and tool signals

}

Tool::~Tool() { }
