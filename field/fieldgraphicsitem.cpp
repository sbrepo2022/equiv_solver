#include "fieldgraphicsitem.h"

FieldGraphicsItem::FieldGraphicsItem(QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->center = QPoint(0, 0);
    this->cell_size = QSizeF(32, 32);
    this->setPos(this->updatedPos());
}

void FieldGraphicsItem::setCenter(const QPoint &center) {
    this->center = center;
    this->setPos(this->updatedPos());
}

void FieldGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
    this->setPos(this->updatedPos());
}
