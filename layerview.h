#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include <QWidget>
#include <QMouseEvent>

/**
 * @brief The LayerView class handles the logic for layer GUI elements
 *
 * @author Alex Lancaster
 * @date March 30, 2025
 */
class LayerView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor for LayerView
     *
     * Initilizes the first layer to 0; default needed as QWidget is promoted to a LayerView
     * @param parent - QWidget that LayerView is the child of
     */
    explicit LayerView(QWidget *parent = nullptr);

    /**
     * @brief Constructor for LayerView that sets the LayerView's index
     * @param index - Index of the layer to be set
     * @param parent - QWidget that LayerView is the child of
     */
    explicit LayerView(int index, QWidget *parent = nullptr);

    /**
     * @brief Index of the layerView object
     */
    int layerIndex;

signals:
    /**
     * @brief Emits when a layer is clicked on with the layer's index
     * @param The index of the layer that was clicked
     */
    void getLayerIndex(int layerIndex);

    /**
     * @brief Emits the index of a layer in the view that was deleted
     * @param The index of the layer which was deleted
     */
    void removeLayerIndex(int layerIndex);

protected:
    /**
     * @brief Overrides the mousePressEvent to make the background a lighter color to indicate clicking
     * @param The mouse event that occured
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Overrides the mouseReleaseEvent to capture that the layer was clicked, restores background color
     * @param The mouse event that occured
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    /**
     * @brief Listens for if a layerView object is removed
     */
    void removeLayer();
};

#endif // LAYERVIEW_H
