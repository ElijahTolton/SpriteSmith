#include "frameview.h"

FrameView::FrameView(QWidget *parent, int index)
    : QPushButton{parent}, frameIndex(index)
{
    setMinimumSize(QSize(100, 100));
    setMaximumSize(QSize(100, 100));
    setStyleSheet("background-color: rgb(0, 0, 0);");

    preview = new QLabel;
    preview->setGeometry(this->geometry());
}

void FrameView::changeIndex(){
    emit getIndex(frameIndex);
}

void FrameView::displayPreview(QPixmap& image) {
    preview->setPixmap(image.scaled(100, 100, Qt::AspectRatioMode::KeepAspectRatio));
}
