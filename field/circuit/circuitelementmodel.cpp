#include "circuitelementmodel.h"

CircuitElementGraphicsItem::CircuitElementGraphicsItem(CircuitElementModel *model, QObject *parent) : FieldGraphicsItem (parent), model(model)
{
    this->color = QColor(0, 0, 0);
    this->hover_color = QColor(220, 20, 0);
    connect(model, &CircuitElementModel::centerChanged, this, &CircuitElementGraphicsItem::setCenter);
    this->setCenter(model->getCenter());
}

CircuitElementGraphicsItem::~CircuitElementGraphicsItem()
{

}

CircuitElementGraphicsItem* CircuitElementGraphicsItem::clone(CircuitElementModel *model)
{
    CircuitElementGraphicsItem *obj_new = new CircuitElementGraphicsItem(model);
    obj_new->setImage(this->image);
    obj_new->setColor(this->color);
    obj_new->setCellSize(this->cell_size);
    obj_new->setCenter(this->center);
    obj_new->setVisibility(this->isVisible());

    return obj_new;
}

QRectF CircuitElementGraphicsItem::boundingRect() const
{
    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();
    QRect cells_rect = this->model->getCellsRect();
    return QRectF(
        QPointF(
            cells_rect.left() * cell_width,
            cells_rect.top() * cell_height
        ),
        QPointF(
            (cells_rect.left() + cells_rect.width()) * cell_width,
            (cells_rect.top() + cells_rect.height()) * cell_height
        )
    );
}

void CircuitElementGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    emit hoverEntered(this);

    QGraphicsItem::hoverEnterEvent(event);
}

void CircuitElementGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsItem::hoverMoveEvent(event);
}

void CircuitElementGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    emit hoverLeaved(this);

    QGraphicsItem::hoverLeaveEvent(event);
}

void CircuitElementGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //emit mousePressed(this, event);
    QGraphicsItem::mousePressEvent(event);
}

QPointF CircuitElementGraphicsItem::updatedPos() {
    return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
}

void CircuitElementGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect target = this->boundingRect().toRect();
    painter->drawImage(target, this->draw_px);

    if (this->debug) {
        QPen debugLines(QColor(255, 0, 0), 1, Qt::DashLine, Qt::SquareCap);
        painter->setPen(debugLines);
        painter->drawRect(this->boundingRect());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void CircuitElementGraphicsItem::updateDrawImage() {
    QColor color = this->mark_hovered ? this->hover_color : this->color;
    for (int y = 0; y < this->draw_px.size().height(); y++) {
        for (int x = 0; x < this->draw_px.size().width(); x++) {
            this->draw_px.setPixelColor(x, y, QColor(
                color.red(),
                color.green(),
                color.blue(),
                this->draw_px.pixelColor(x, y).alpha()
            ));
        }
    }
}

void CircuitElementGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
    this->setPos(this->updatedPos());
}

void CircuitElementGraphicsItem::paramsUpdated()
{
    this->updateDrawImage();
    this->FieldGraphicsItem::paramsUpdated();
}

void CircuitElementGraphicsItem::setCenter(const QPoint &center) {
    this->center = center;
    this->setPos(this->updatedPos());
}

void CircuitElementGraphicsItem::setImage(const QImage &image)
{
    this->image = image;
    this->draw_px = image.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    this->paramsUpdated();
}

void CircuitElementGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
    this->paramsUpdated();
}

void CircuitElementGraphicsItem::setHoverColor(const QColor &hover_color)
{
    this->hover_color = hover_color;
    this->paramsUpdated();
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
    this->id = object_count++;

    this->angle = 0;
    this->cells_rect = QRect(0, 0, 1, 1);

    this->graphics_item = new CircuitElementGraphicsItem(this);
}

CircuitElementModel::CircuitElementModel(const CircuitElementModel &obj)
{
    this->id = object_count++;

    this->angle = obj.angle;
    this->cells_rect = obj.cells_rect;
    this->center = obj.center;
    this->graphics_item = obj.graphics_item->clone(this);
}

CircuitElementModel::~CircuitElementModel()
{
    delete this->graphics_item;
}

int CircuitElementModel::object_count = 0;

