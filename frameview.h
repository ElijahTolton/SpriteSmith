#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QPushButton>
#include <QLabel>
#include <frame.h>

/**
 * @brief The FrameView
 * Class that allows the user to click on each frame and change which frame is selected.
 */
class FrameView : public QPushButton
{
    Q_OBJECT
public:
    // intialize first frame to 0 index
    explicit FrameView(QWidget *parent = nullptr, int index = 0);

public slots:
    void changeIndex();
    void displayPreview(QPixmap image);
    void requestRepaint();

signals:
    // Gives the current index of the frame clicked.
    void getIndex(int index);

    void repaintSignal(int index);

private:
    int frameIndex;
    QLabel *preview;
};

#endif // FRAMEVIEW_H
