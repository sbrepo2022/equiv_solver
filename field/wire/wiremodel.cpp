#include "wiremodel.h"

WireGraphicsItem::WireGraphicsItem(WireModel *model, QObject *parent) : FieldGraphicsItem (parent), model(model)
{
    this->line_color = QColor(0, 0, 0);
    this->line_width = 3;
    connect(model, &WireModel::centerChanged, this, &WireGraphicsItem::setCenter);
    this->setCenter(model->getCenter());
}

WireGraphicsItem::~WireGraphicsItem()
{

}

WireGraphicsItem* WireGraphicsItem::clone(WireModel *model)
{
    WireGraphicsItem *obj_new = new WireGraphicsItem(model);
    obj_new->setLineColor(this->line_color);
    obj_new->setLineWidth(this->line_width);
    obj_new->setCellSize(this->cell_size);
    obj_new->setCenter(this->center);
    obj_new->setVisibility(this->isVisible());

    return obj_new;
}

QRectF WireGraphicsItem::boundingRect() const  // ????
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

QPointF WireGraphicsItem::updatedPos() { // ???
    return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
}

void WireGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) // ???
{
    QPen penLines(this->line_color, this->line_width, Qt::SolidLine, Qt::RoundCap);
    painter->setPen(penLines);

    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();

    WireDirection first_direction = this->model->getFirstDirection();
    WireDirection second_direction = this->model->getSecondDirection();
    QLineF first_line = this->getLineWithWireDirection(this->model->getCenter(), first_direction);
    QLineF second_line = this->getLineWithWireDirection(first_line.p2(), second_direction);

    painter->drawLine(first_line);
    painter->drawLine(second_line);


    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QLineF WireGraphicsItem::getLineWithWireDirection(QPoint start_point, WireDirection wire_direction)
{
    QPoint end_point;

    switch (wire_direction.getType()) {
        case WireDirectionType::TOP:
            end_point = QPoint(start_point.x(), start_point.y() - wire_direction.getLength());
            break;

        case WireDirectionType::BOTTOM:
            end_point = QPoint(start_point.x(), start_point.y() + wire_direction.getLength());
            break;

        case WireDirectionType::LEFT:
            end_point = QPoint(start_point.x() - wire_direction.getLength(), start_point.y());
            break;

        case WireDirectionType::RIGHT:
            end_point = QPoint(start_point.x() + wire_direction.getLength(), start_point.y());
            break;
    }

    QPointF start_point_f = QPointF(start_point.x());

    return QLineF(start_point, end_point);
}

void WireGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
    this->setPos(this->updatedPos());
}

void WireGraphicsItem::setCenter(const QPoint &center) {
    this->center = center;
    this->setPos(this->updatedPos());
}

void WireGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
}

void WireGraphicsItem::setLineWidth(qreal line_width)
{
    this->line_width = line_width;
}

void WireGraphicsItem::setVisibility(bool visible) {
    if (visible) {
        this->show();
    }
    else {
        this->hide();
    }
}


WireModel::WireModel(QObject *parent) : QObject(parent)
{
    this->id = object_count++;

    this->cells_rect = QRect(0, 0, 0, 0);

    this->graphics_item = new WireGraphicsItem(this);
}

WireModel::WireModel(const WireModel &obj)
{
    this->id = object_count++;

    this->cells_rect = obj.cells_rect;
    this->first_direction = obj.first_direction;
    this->second_direction = obj.second_direction;
    this->center = obj.center;
    this->graphics_item = obj.graphics_item->clone(this);
}

WireModel::~WireModel()
{
    delete this->graphics_item;
}

int WireModel::object_count = 0;

