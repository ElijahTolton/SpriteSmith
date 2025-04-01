#include "frameview.h"
#include <QDebug>

FrameView::FrameView(QWidget *parent, int index)
    : QPushButton{parent}, frameIndex(index)
{
    setMinimumSize(QSize(100, 100));
    setMaximumSize(QSize(100, 100));
    setStyleSheet("background-color: rgb(0, 0, 0);");
    frameIndex = index;

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
