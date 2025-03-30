#include "layer.h"
#include "qjsonarray.h"
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
    qDebug() << "Rotating layer, original size:" << image.size();
    QTransform transform;
    transform.rotate(90);
    // Use a transformation mode (e.g., Qt::FastTransformation or Qt::SmoothTransformation)
    QImage rotated = image.transformed(transform, Qt::FastTransformation);
    qDebug() << "Rotated image size:" << rotated.size();
    image = rotated;
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


void Layer::drawPixel(QColor color, int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        image.setPixelColor(x, y, color);
    }
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

void Layer::setActive(bool active){
    this->active = active;
}


Layer::Layer(QJsonObject json){
    try{

        width = json["width"].toInt();
        height = json["height"].toInt();
        active = json["active"].toBool();
        image = QImage(width, height, QImage::Format_RGBA8888);

        // Ensure the image is filled with transparent color initially
        image.fill(Qt::transparent);

        // Parse the pixels array from the JSON object and set the pixel colors
        QJsonArray pixelArray = json["pixels"].toArray();

        int index = 0;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (index < pixelArray.size()) {
                    QJsonObject pixelObj = pixelArray[index].toObject();
                    QColor pixelColor(
                        pixelObj["r"].toInt(),
                        pixelObj["g"].toInt(),
                        pixelObj["b"].toInt(),
                        pixelObj["a"].toInt()
                    );
                    image.setPixelColor(x, y, pixelColor);
                }
                ++index;
            }
        }
    } catch(std::exception){
        qWarning() << "Error parsing LayerJson";
    }
}
