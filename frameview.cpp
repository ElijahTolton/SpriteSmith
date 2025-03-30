#include "frameview.h"

FrameView::FrameView(int index, QWidget *parent)
    : QPushButton{parent}, frameIndex(index)
{
    setMinimumSize(QSize(100, 100));
    setMaximumSize(QSize(100, 100));
    setStyleSheet("background-color: rgb(255, 0, 0);");
}

FrameView::FrameView(QWidget *parent)
    : QPushButton{parent}, frameIndex(0)
{
    setMinimumSize(QSize(100, 100));
    setMaximumSize(QSize(100, 100));
    setStyleSheet("background-color: rgb(255, 0, 0);");
}

void FrameView::changeIndex(){
    emit getIndex(frameIndex);
    qDebug() << frameIndex;
}
