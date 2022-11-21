#include "gridmodel.h"

GridGraphicsItem::GridGraphicsItem(GridModel *model, QObject *parent) : FieldGraphicsItem(parent), model(model)
{
    this->line_width = 1;
    this->line_color = QColor(220, 220, 220);
    this->last_hover_cell = QPoint(-1, -1);

    this->setAcceptHoverEvents(true);
}

GridGraphicsItem::~GridGraphicsItem()
{

}

void GridGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pos = event->pos();
    QPoint cur_hover_cell = QPoint(pos.x() / this->cell_size.width(), pos.y() / this->cell_size.height());
    if (cur_hover_cell != this->last_hover_cell) {
        emit onCellLeave(this->last_hover_cell);
        emit onCellEnter(cur_hover_cell);
        this->last_hover_cell = cur_hover_cell;
    }
    QGraphicsItem::hoverMoveEvent(event);
}

void GridGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->last_hover_cell = QPoint(-1, -1);
    emit onItemEnter();
    QGraphicsItem::hoverEnterEvent(event);
}

void GridGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->last_hover_cell = QPoint(-1, -1);
    emit onItemLeave();
    QGraphicsItem::hoverLeaveEvent(event);
}

void GridGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    QPoint cur_pressed_cell = QPoint(pos.x() / this->cell_size.width(), pos.y() / this->cell_size.height());
    emit onCellPressed(cur_pressed_cell);
}

void GridGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penLines(this->line_color, this->line_width, Qt::SolidLine, Qt::SquareCap);
    painter->setPen(penLines);

    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();

    for (int x = 0; x < this->model->getGridSize().width() - 1; x++) {
        painter->drawLine(
            QPointF(x * cell_width + cell_width, 0),
            QPointF(x * cell_width + cell_width, this->model->getGridSize().height() * cell_height)
        );
    }

    for (int y = 0; y < this->model->getGridSize().height() - 1; y++) {
        painter->drawLine(
            QPointF(0, y * cell_height + cell_height),
            QPointF(this->model->getGridSize().width() * cell_width, y * cell_height + cell_height)
        );
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF GridGraphicsItem::boundingRect() const
{
    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();
    return QRectF(0, 0, this->model->getGridSize().width() * cell_width, this->model->getGridSize().height() * cell_height);
}



GridModel::GridModel(QObject *parent) : QObject(parent)
{
    this->grid_size = QSize(20, 20);

    this->graphics_item = new GridGraphicsItem(this);
}

GridModel::~GridModel()
{
    delete this->graphics_item;
}

