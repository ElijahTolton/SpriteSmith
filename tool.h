/**
 * @brief
 * Header file for Tool model class that handles all
 * tool actions from MainWindow class
 *
 * @authors
 * Landon Huking
 *
 * @date
 * Created:         3/25/25
 * Last modified:   3/27/25
 */

#ifndef TOOL_H
#define TOOL_H

#include <QMainWindow>
#include <QString>
#include <QColor>
#include <layer.h>

class Tool : QWidget
{
public:
    Tool(QMainWindow* window, Layer* activeLayer);
    ~Tool();

private:
    QString name;
    QColor color;
    QMainWindow* window;
    Layer* activeLayer;

signals:
    void editSignal(QColor color, int x, int y);

private slots:
    void onEdit(QColor color, int x, int y);

};

#endif // TOOL_H
