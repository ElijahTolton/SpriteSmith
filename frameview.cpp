#include "frameview.h"
#include <QDebug>

/**
 * @brief The FrameView
 * Class that allows the user to click on each frame and change which frame is selected.
 *
 * @author Elijah Tolton & Alex Lancaster (documentation)
 * @date March 30, 2025
 */

FrameView::FrameView(QWidget *parent, int index)
    : QPushButton{parent}, frameIndex(index)
{
    setMinimumSize(QSize(100, 100));
    setMaximumSize(QSize(100, 100));
    setStyleSheet("background-color: rgb(0, 0, 0);");

    preview = new QLabel(this);
    preview->setGeometry(0, 0, width(), height());
    preview->setAlignment(Qt::AlignCenter);
    preview->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void FrameView::changeIndex(){
    emit getIndex(frameIndex);
}

void FrameView::requestRepaint() {
    qDebug() << "requesting " << frameIndex;
    emit repaintSignal(frameIndex);
}

void FrameView::displayPreview(QPixmap image) {
    preview->setPixmap(image.scaled(preview->size()));
}
