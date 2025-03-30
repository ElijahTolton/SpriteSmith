#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QPushButton>

/**
 * @brief The FrameView
 * Class that allows the user to click on each frame and change which frame is selected.
 */
class FrameView : public QPushButton
{
    Q_OBJECT
public:
    // intialize first frame to 0 index
    explicit FrameView(QWidget *parent = nullptr);
    explicit FrameView(int index = 0, QWidget *parent = nullptr);

public slots:
    void changeIndex();

signals:
    // Gives the current index of the frame clicked.
    void getIndex(int index);

private:
    int frameIndex;
};

#endif // FRAMEVIEW_H
