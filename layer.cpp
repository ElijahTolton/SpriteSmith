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

QJsonObject Layer::toJSON() const {
    // Create a JSON object to hold the layer data
    QJsonObject jsonObj;

    // Add width, height, and active status to the JSON object
    jsonObj["width"] = width;
    jsonObj["height"] = height;
    jsonObj["active"] = active;

    // Create a JSON array to hold pixel data
    QJsonArray pixelArray;

    // Iterate through each pixel in the image and add its RGBA values to the array
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor pixelColor(image.pixel(x, y));

            // Create a JSON object for each pixel with its RGBA values
            QJsonObject pixelObj;
            pixelObj["r"] = pixelColor.red();
            pixelObj["g"] = pixelColor.green();
            pixelObj["b"] = pixelColor.blue();
            pixelObj["a"] = pixelColor.alpha();

            // Add the pixel object to the array
            pixelArray.append(pixelObj);
        }
    }

    // Add the pixel array to the JSON object
    jsonObj["pixels"] = pixelArray;

    return jsonObj;
}
