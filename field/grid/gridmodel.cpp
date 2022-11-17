#include "gridmodel.h"

GridGraphicsItem::GridGraphicsItem(GridModel *model, QObject *parent) : FieldGraphicsItem(parent), model(model)
{
    this->line_width = 1;
    this->line_color = QColor(220, 220, 220);
}

GridGraphicsItem::~GridGraphicsItem()
{

}

void GridGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penLines(this->line_color, this->line_width, Qt::SolidLine, Qt::SquareCap);
    painter->setPen(penLines);

    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();

    for (int x = 0; x < this->model->getWidth() - 1; x++) {
        painter->drawLine(
            QPointF(x * cell_width + cell_width, 0),
            QPointF(x * cell_width + cell_width, this->model->getHeight() * cell_height)
        );
    }

    for (int y = 0; y < this->model->getHeight() - 1; y++) {
        painter->drawLine(
            QPointF(0, y * cell_height + cell_height),
            QPointF(this->model->getWidth() * cell_width, y * cell_height + cell_height)
        );
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF GridGraphicsItem::boundingRect() const
{
    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();
    return QRectF(0, 0, this->model->getWidth() * cell_width, this->model->getHeight() * cell_height);
}



GridModel::GridModel(QObject *parent) : QObject(parent)
{
    this->width = 20;
    this->height = 20;
}

GridGraphicsItem* GridModel::createGridGraphicsItem() {
    return new GridGraphicsItem(this);
}
