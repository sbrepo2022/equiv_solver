#include "circuitelementmodel.h"

CircuitElementGraphicsItem::CircuitElementGraphicsItem(CircuitElementModel *model, QObject *parent) : FieldGraphicsItem (parent), model(model)
{
    this->color = QColor(0, 0, 0);
}

CircuitElementGraphicsItem::~CircuitElementGraphicsItem()
{

}

QRectF CircuitElementGraphicsItem::boundingRect() const
{
    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();
    QRect cells_rect = this->model->getCellsRect();
    return QRectF(
        QPointF(
            (-0.5 + cells_rect.left()) * cell_width,
            (-0.5 + cells_rect.top()) * cell_height
        ),
        QPointF(
            (0.5 + cells_rect.right()) * cell_width,
            (0.5 + cells_rect.bottom()) * cell_height
        )
    );
}

void CircuitElementGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect target = this->boundingRect().toRect();
    painter->drawPixmap(target, this->draw_px);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void CircuitElementGraphicsItem::updateDrawImage() {
    this->draw_px.fill(this->color);
    this->draw_px.setMask(QBitmap::fromImage(this->image.createAlphaMask()));
}

void CircuitElementGraphicsItem::setImage(const QImage &image)
{
    this->image = image;
    this->draw_px = QPixmap(this->image.size());
    updateDrawImage();
}

void CircuitElementGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
    updateDrawImage();
}





CircuitElementModel::CircuitElementModel(QObject *parent) : QObject(parent)
{
    this->angle = 0;
    this->cells_rect = QRect(0, 0, 1, 1);
}

CircuitElementGraphicsItem* CircuitElementModel::createCircuitElementGraphicsItem()
{
    return new CircuitElementGraphicsItem(this);
}
