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

QPoint GridGraphicsItem::getCellByMousePos(const QPointF &pos)
{
    return QPoint(pos.x() / this->cell_size.width(), pos.y() / this->cell_size.height());
}

void GridGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pos = event->pos();
    QPoint cur_hover_cell = getCellByMousePos(pos);
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
    QPoint cur_pressed_cell = getCellByMousePos(pos);
    emit onCellPressed(cur_pressed_cell);
}

void GridGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penLines(this->line_color, 1, Qt::SolidLine, Qt::SquareCap);
    painter->setPen(penLines);

    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();

    for (int x = 0; x < this->model->getGridSize().width(); x++) {
        painter->drawLine(
            QPointF(x * cell_width + cell_width * 0.5, 0),
            QPointF(x * cell_width + cell_width * 0.5, this->model->getGridSize().height() * cell_height)
        );
    }

    for (int y = 0; y < this->model->getGridSize().height(); y++) {
        painter->drawLine(
            QPointF(0, y * cell_height + cell_height * 0.5),
            QPointF(this->model->getGridSize().width() * cell_width, y * cell_height + cell_height * 0.5)
        );
    }

    /*
    for (int x = 0; x < this->model->getGridSize().width(); x++) {
        for (int y = 0; y < this->model->getGridSize().height(); y++) {
            painter->drawPoint(
                QPointF(x * cell_width + cell_width * 0.5, y * cell_height + cell_height * 0.5)
            );
        }
    }
    */

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
    this->grid_size = QSize(250, 250);

    this->graphics_item = new GridGraphicsItem(this);
}

GridModel::~GridModel()
{
    delete this->graphics_item;
}

