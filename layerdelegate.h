#ifndef LAYERDELEGATE_H
#define LAYERDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

/**
 * @brief Custom delegate for rendering layers with a border
 *
 * @authors Dean Smith & Alex Lancaster (documentation)
 * @date March 31, 2025
 */
class LayerDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    /**
     * @brief Constructs a LayerDelegate.
     * @param parent The parent QObject, defaults to nullptr.
     */
    explicit LayerDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    /**
     * @brief Paints the delegate item.
     * @param painter The QPainter used to draw the item.
     * @param option Style options for the item.
     * @param index The model index of the item being drawn.
     *
     * This method:
     * - Retrieves the background color from Qt::BackgroundRole.
     * - Retrieves the border color from Qt::UserRole.
     * - Draws the background and a border if a valid border color is provided.
     * - Calls the base class's paint method to render text and icons.
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QColor borderColor = index.data(Qt::UserRole).value<QColor>();  // Retrieve stored border color

        // Draw background
        painter->fillRect(option.rect, index.data(Qt::BackgroundRole).value<QColor>());

        // Draw border
        if (borderColor.isValid()) {
            QPen pen(borderColor, 1);  // Border width = 2px
            painter->setPen(pen);
            painter->drawRect(option.rect.adjusted(1, 1, -1, -1));  // Avoid overlapping neighboring borders
        }

        // Call base class to draw text/icons
        QStyledItemDelegate::paint(painter, option, index);
    }
};

#endif // LAYERDELEGATE_H
