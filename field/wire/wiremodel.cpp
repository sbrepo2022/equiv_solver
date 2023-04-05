#include "wiremodel.h"
#include <cmath>

WireGraphicsItem::WireGraphicsItem(WireModel *model, QObject *parent) : FieldGraphicsItem (parent), model(model)
{
    this->line_color = QColor(0, 0, 0);
    this->line_hover_color = QColor(220, 20, 0);
    this->line_width = 4;
    this->line_hover_distance_factor = 1.0;
    connect(model, &WireModel::centerChanged, this, &WireGraphicsItem::setCenter);
    connect(model, &WireModel::pointsChanged, this, &WireGraphicsItem::paramsUpdated);
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
            (cells_rect.left() - 1) * cell_width,
            (cells_rect.top() - 1) * cell_height
        ),
        QPointF(
            (cells_rect.left() + cells_rect.width()) * cell_width,
            (cells_rect.top() + cells_rect.height()) * cell_height
        )
    );
}

QPainterPath WireGraphicsItem::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    if (this->model == nullptr) return path;
    QPolygonF polyline_f = this->model->getPoints();
    QTransform transform;
    transform = transform.scale(this->cell_size.width(),this->cell_size.height());
    QPolygonF points = transform.map(polyline_f);

    qreal dist = (this->cell_size.width() + this->cell_size.height()) / 2 * this->line_hover_distance_factor;

    for (int i = 0; i < points.count() - 1; i++) {
        QPointF a = points[i + 1] - points[i];
        QPointF n = QPointF(-a.y(), a.x());
        if (n.manhattanLength() != 0.0) n = n / n.manhattanLength();

        QVector<QPointF> bounding_points = {
            points[i + 1] + n * dist,
            points[i] + n * dist,
            points[i] - n * dist,
            points[i + 1] - n * dist,
        };
        QPolygonF bounding_polygon(bounding_points);
        path.addPolygon(bounding_polygon);
    }

    return path;
}

void WireGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);

    emit hoverEntered(this);
}

void WireGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void WireGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);

    emit hoverLeaved(this);
}

void WireGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    emit mousePressed(this, event);
}

QPointF WireGraphicsItem::updatedPos() {
    return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
}

void WireGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penLines(this->mark_hovered ? this->line_hover_color : this->line_color, this->line_width, Qt::SolidLine, Qt::SquareCap);
    painter->setPen(penLines);

    QPolygonF polyline_f = this->model->getPoints();
    QTransform transform;
    transform = transform.scale(this->cell_size.width(),this->cell_size.height());
    QPolygonF polyline_f_2 = transform.map(polyline_f);
    painter->drawPolyline(polyline_f_2);

    if (this->debug) {
        QPen debugLines(QColor(255, 0, 0), 1, Qt::DashLine, Qt::SquareCap);
        painter->setPen(debugLines);
        painter->drawRect(this->boundingRect());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void WireGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
    this->setPos(this->updatedPos());
}

void WireGraphicsItem::setCenter(const QPoint &center) {
    this->center = center;
    this->setPos(this->updatedPos());
}

void WireGraphicsItem::setLineHoverColor(const QColor &line_hovered_color)
{
    this->line_hover_color = line_hovered_color;
    this->paramsUpdated();
}

void WireGraphicsItem::setLineColor(const QColor &line_color)
{
    this->line_color = line_color;
    this->paramsUpdated();
}

void WireGraphicsItem::setLineWidth(qreal line_width)
{
    this->line_width = line_width;
    this->paramsUpdated();
}

void WireGraphicsItem::setLineHoverDistanceFactor(qreal line_hover_distance_factor)
{
    this->line_hover_distance_factor = line_hover_distance_factor;
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

WireModel::WireModel(const WireModel &obj) : QObject(obj.parent())
{
    this->id = object_count++;

    this->cells_rect = obj.cells_rect;
    this->points = obj.points;
    this->center = obj.center;
    this->graphics_item = obj.graphics_item->clone(this);
}

WireModel::~WireModel()
{
    delete this->graphics_item;
}

int WireModel::object_count = 0;

void WireModel::updateCellsRect()
{
    this->cells_rect = this->points.boundingRect();
}

