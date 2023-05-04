#include "gridgraphicsitem.h"

GridGraphicsItem::GridGraphicsItem(QObject *parent) : FieldGraphicsItem(parent), QGraphicsItem()
{
    this->width = 20;
    this->height = 20;
    this->cellWidth = 32;
    this->cellHeight = 32;
}

GridGraphicsItem::~GridGraphicsItem()
{

}

void GridGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penLines(QColor(220, 220, 220), 1, Qt::SolidLine, Qt::SquareCap);
    painter->setPen(penLines);

    for (int x = 0; x < this->width - 1; x++) {
        painter->drawLine(
            QPointF(x * this->cellWidth + this->cellWidth, 0),
            QPointF(x * this->cellWidth + this->cellWidth, this->height * this->cellHeight)
        );
    }

    for (int y = 0; y < this->height - 1; y++) {
        painter->drawLine(
            QPointF(0, y * this->cellHeight + this->cellHeight),
            QPointF(this->width * this->cellWidth, y * this->cellHeight + this->cellHeight)
        );
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF GridGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, this->width * this->cellWidth, this->height * this->cellHeight);
}
