#include "fieldgraphicsitem.h"

FieldGraphicsItem::FieldGraphicsItem(QObject *parent) :
    QObject(parent),
    QGraphicsItem()
{
    this->cell_size = QSizeF(32, 32);
    this->debug = false;
}

void FieldGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
}
