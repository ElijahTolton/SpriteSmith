#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QPushButton>

/**
 * @brief The FrameView
 * Class that allows the user to click on each frame and change which frame is selected.
 *
 * @author Elijah Tolton and Alex Lancaster
 * @date March 30, 2025
 */
class FrameView : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a new GUI frame with the first frame having index 0
     * @param parent - QWidget parent of FrameView, defaults to nullptr
     */
    explicit FrameView(QWidget *parent = nullptr);

    /**
     * @brief Constructs a new GUI frame with a specified index; index defaults to 0
     * @param index - index of the frame to be created
     * @param parent - QWidget parent of FrameView, defaults to nullptr
     */
    explicit FrameView(int index = 0, QWidget *parent = nullptr);

public slots:
    /**
     * @brief changeIndex is called whenever a frame in the frame preview is clicked
     */
    void changeIndex();

signals:
    // Gives the current index of the frame clicked.
    /**
     * @brief getIndex is sent whenever a frame in the frame preview is clicked
     * @param index - the current index of the frame in the frame preview
     */
    void getIndex(int index);

private:
    /**
     * @brief frameIndex is the current index of a frame in the frame preview
     */
    int frameIndex;
};

#endif // FRAMEVIEW_H
