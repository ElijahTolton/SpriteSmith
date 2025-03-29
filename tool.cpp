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

Tool::Tool(QMainWindow* window, QWidget* layer ) : window(window), layer(layer) {

    //TO DO: Add connections between window signals and tool slots

    //TO DO: Add connections between tool slots and tool signals

}

void Tool::onEdit(int x, int y) {
    emit editSignal(color, x, y);
}

void Tool::onColorChange(QColor color) {
    this->color = color;
}

void Tool::onToolChange(QString name) {
    this->name = name;
}
