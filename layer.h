#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QJsonObject>

/**
 * @brief The Layer class
 *
 * A layer is the current image the user is drawing.
 * There can be multiple layers, and higher level layers will cover
 * lower level layers.
 *
 * @authors Dean Smith, Elijah Tolton, Alex Lancaster
 * @date March 30, 2025
 */
class Layer
{
public:
    /**
     * @brief Constructs a Layer of specificed width and height
     *
     * Creates a new QImage based on the width and height, and sets
     * the background of the layer to transparent.
     *
     * @param width - the desired width of the layer
     * @param height - the desired height of the layer
     */
    Layer(int width, int height);

    /**
     * @brief Constructs a copy of a layer
     * @param layer - instance of the layer to be copied
     */
    Layer(Layer const &layer);

    /**
     * @brief overrides the assignment '=' operator for Layer
     * @param other The layer instance to copy
     * @return A reference to the current Layer after assignment
     */
    Layer& operator=(const Layer &other);

    /**
     * @brief isActive returns if the current layer is the active layer in use
     * @return true if the current layer is the active layer, false otherwise
     */
    bool isActive() const;

    /**
     * @brief getImage gets the current image from the layer
     * @return The layer's current image
     */
    QImage& getImage();

    /**
     * @brief setActive sets the current layer to become the active layer
     * @param active - true to set the current layer to be the active layer, false otherwise
     */
    void setActive(bool active);

    /**
     * @brief mirrors the current layer's image
     */
    void mirror();

    /**
     * @brief rotates the current layer's image
     */
    void rotate();

    /**
     * @brief overrides the equality '==' operator
     *
     * Checks if layers are equal by comparing width, height, and image for equality
     *
     * @param layer - layer to compare equality
     * @return true if layer's width, height, and image are the same, false otherwise
     */
    bool operator==(const Layer &layer) const;

    /**
     * @brief toJSON converts the Layer object to a JSON representation
     *
     * Serializes width, height, active status and image.
     * Image is stored as A JSON array of pixel data, where each pixel is represented by its RGBA values.
     *
     * @return A QJsonObject containing the layer's properties and pixel data.
     */
    QJsonObject toJSON() const;

    /**
     * @brief drawPixel stores a pixel in the layer's image at a given x, y for a given color
     * @param color - the color of the pixel to be stored
     * @param x - the current x position in the canvas
     * @param y - the current y position in the canvas
     */
    void drawPixel(QColor color, int x, int y);

    /**
     * @brief Constructs a Layer object from a QJsonObject
     * @param json A QJsonObject containing the layer's properties and pixel data
     */
    Layer(QJsonObject);

private:
    /**
     * @brief The layer's current image
     */
    QImage image;

    /**
     * @brief The layer's active status
     *
     * There should only be only active layer at a time.
     */
    bool active;

    /**
     * @brief The width of the Layer
     */
    int width;

    /**
     * @brief The height of the Layer
     */
    int height;
};

#endif // LAYER_H
