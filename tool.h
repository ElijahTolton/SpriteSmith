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

class Tool : QWidget
{
public:
    Tool(QMainWindow* window, QWidget* layer);
    ~Tool();

private:
    QString name;
    QColor color;
    QMainWindow* window;
    QWidget* layer;

signals:
    void editSignal(QColor color, int x, int y);

public slots:
    void onEdit(int x, int y);
    void onColorChange(QColor color);
    void onToolChange(QString name);
};

#endif // TOOL_H
