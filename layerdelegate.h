#ifndef LAYERDELEGATE_H
#define LAYERDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class LayerDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit LayerDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

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
