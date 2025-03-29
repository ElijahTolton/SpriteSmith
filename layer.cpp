#include "layer.h"
#include <QImage>

Layer::Layer(int width, int height) :
    image(width, height, QImage::Format_RGBA8888), width(width), height(height) {
    image.fill(Qt::transparent);
}

Layer::Layer(Layer const &layer) :
    image(layer.image), width(layer.width), height(layer.height){
}

Layer& Layer::operator=(const Layer &layer) {
    if (this != &layer) {  // Prevent self-assignment
        image = layer.image;
        width = layer.width;
        height = layer.height;
    }
    return *this;
}

bool Layer::isActive() const{ return active; }
QImage& Layer::getImage() { return image; }

void Layer::mirror() {
    image = image.mirrored(true, false); //"(true, false)" means horizontal mirroring
}

void Layer::rotate() {
    QTransform transform;
    transform.rotate(90);
    image = image.transformed(transform);
}

bool Layer::operator==(const Layer &layer) const {
    // Compare width, height, and image for equality
    return (this->width == layer.width) &&
           (this->height == layer.height) &&
           (this->image == layer.image);
}

void Layer::setShown(bool active){
    this->active = active;
}

