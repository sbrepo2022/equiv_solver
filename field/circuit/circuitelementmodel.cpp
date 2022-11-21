#include "circuitelementmodel.h"

CircuitElementGraphicsItem::CircuitElementGraphicsItem(CircuitElementModel *model, QObject *parent) : FieldGraphicsItem (parent), model(model)
{
    this->color = QColor(0, 0, 0);
    connect(model, &CircuitElementModel::centerChanged, this, &CircuitElementGraphicsItem::setCenter);
}

CircuitElementGraphicsItem::~CircuitElementGraphicsItem()
{
    disconnect(model, &CircuitElementModel::centerChanged, this, &CircuitElementGraphicsItem::setCenter);
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

QPointF CircuitElementGraphicsItem::updatedPos() {
    return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
}

void CircuitElementGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect target = this->boundingRect().toRect();
    painter->drawImage(target, this->draw_px);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void CircuitElementGraphicsItem::updateDrawImage() {
    for (int y = 0; y < this->draw_px.size().height(); y++) {
        for (int x = 0; x < this->draw_px.size().width(); x++) {
            this->draw_px.setPixelColor(x, y, QColor(
                this->color.red(),
                this->color.green(),
                this->color.blue(),
                this->draw_px.pixelColor(x, y).alpha()
            ));
        }
    }
}

void CircuitElementGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
    this->setPos(this->updatedPos());
}

void CircuitElementGraphicsItem::setCenter(const QPoint &center) {
    this->center = center;
    this->setPos(this->updatedPos());
}

void CircuitElementGraphicsItem::setImage(const QImage &image)
{
    this->image = image;
    this->draw_px = image.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    updateDrawImage();
}

void CircuitElementGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
    updateDrawImage();
}

void CircuitElementGraphicsItem::setVisibility(bool visible) {
    if (visible) {
        this->show();
    }
    else {
        this->hide();
    }
}




CircuitElementModel::CircuitElementModel(QObject *parent) : QObject(parent)
{
    this->angle = 0;
    this->cells_rect = QRect(0, 0, 1, 1);
}

CircuitElementModel::~CircuitElementModel()
{

}

CircuitElementModel* CircuitElementModel::clone()
{

}

CircuitElementGraphicsItem* CircuitElementModel::createCircuitElementGraphicsItem()
{
    CircuitElementGraphicsItem* graphics_item = new CircuitElementGraphicsItem(this);
    this->graphics_items.push_back(graphics_item);
    return graphics_item;
}
