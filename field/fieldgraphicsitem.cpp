#include "fieldgraphicsitem.h"

FieldGraphicsItem::FieldGraphicsItem(QObject *parent) :
    QObject(parent),
    QGraphicsItem()
{
    this->cell_size = QSizeF(32, 32);
}

void FieldGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
}
