#include "circuitelementmodel.h"

CircuitElementGraphicsItem::CircuitElementGraphicsItem(QObject *parent) : FieldGraphicsItem(parent)
{
    this->init();
}

CircuitElementGraphicsItem::CircuitElementGraphicsItem(const CircuitElementGraphicsItem &obj) : FieldGraphicsItem(obj)
{
    this->init();

    this->image = obj.image;
    this->color = obj.color;
    this->hover_color = obj.hover_color;
    this->selection_color = obj.selection_color;
    this->disable_color = obj.disable_color;
    this->center = obj.center;

    this->setCenter(obj.center);
    this->setImage(obj.image);
    this->setVisibility(obj.isVisible());
}

void CircuitElementGraphicsItem::init()
{
    this->color = QColor(0, 0, 0);
    this->hover_color = QColor(220, 20, 0);
    this->selection_color = QColor(200, 20, 0);
    this->disable_color = QColor(50, 50, 50);
}

void CircuitElementGraphicsItem::attachFieldElementModel()
{
    CircuitElementModel *model = this->getModel<CircuitElementModel>();
    if (model == nullptr) return;

    connect(model, &CircuitElementModel::centerChanged, this, &CircuitElementGraphicsItem::setCenter);
    this->setCenter(model->getCenter());
}

void CircuitElementGraphicsItem::detachFieldElementModel()
{
    CircuitElementModel *model = this->getModel<CircuitElementModel>();
    if (model == nullptr) return;

    disconnect(model, &CircuitElementModel::centerChanged, this, &CircuitElementGraphicsItem::setCenter);
}

CircuitElementGraphicsItem::~CircuitElementGraphicsItem()
{

}

QRectF CircuitElementGraphicsItem::getBasicRect() const
{
    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();
    QRect cells_rect = this->getModel<CircuitElementModel>()->getCellsRect();
    // Уменьшение размеров прямоугольника коллизии на 0.01 необходимо для возможности размещять рядом элементы
    return QRectF(
        QPointF(
            cells_rect.left() * cell_width + 0.01,
            cells_rect.top() * cell_height + 0.01
        ),
        QPointF(
            (cells_rect.left() + cells_rect.width()) * cell_width - 0.01,
            (cells_rect.top() + cells_rect.height()) * cell_height - 0.01
        )
    );
}

QRectF CircuitElementGraphicsItem::boundingRect() const
{
    QRectF basic_rect = this->getBasicRect();

    basic_rect += QMarginsF(10, 10, 10, 10);

    return basic_rect;
}

QPainterPath CircuitElementGraphicsItem::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(this->getBasicRect());

    if (this->getModel<CircuitElementModel>() != nullptr) {
        int angle = this->getModel<CircuitElementModel>()->getAngle();
        QHash<QPoint, InputPointData> inputs_points = this->getModel<CircuitElementModel>()->getInputsPoints();
        for (InputPointData input_point_data : inputs_points.values()) {
            InputPointData input_point_data_rotated = input_point_data.withAngle(angle);

            path.addRect(input_point_data_rotated.calculateInputRect(this->cell_size, 0.1, 0.02));
        }
    }

    return path;
}

void CircuitElementGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsItem::hoverEnterEvent(event);

    emit hoverEntered(this);
}

void CircuitElementGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsItem::hoverMoveEvent(event);
}

void CircuitElementGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsItem::hoverLeaveEvent(event);

    emit hoverLeaved(this);
}

void CircuitElementGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    emit mousePressed(this, event);
}

QPointF CircuitElementGraphicsItem::updatedPos() {
    return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
}

void CircuitElementGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect target = this->getBasicRect().toRect();
    if (this->getModel<CircuitElementModel>() != nullptr) painter->rotate(this->getModel<CircuitElementModel>()->getAngle() * 90);
    painter->drawImage(target, this->draw_px);
    if (this->getModel<CircuitElementModel>() != nullptr) painter->rotate(-this->getModel<CircuitElementModel>()->getAngle() * 90);

    QPointF element_center = this->getBasicRect().center();
    if (this->mark_collided) {
        forbidden_renderer.render(painter, QRectF(-this->cell_size.width() / 2 * 4 + element_center.x(), -this->cell_size.height() / 2 * 4 + element_center.y(),
                                                  this->cell_size.width() * 4, this->cell_size.height() * 4));
    }

    if (this->debug) {
        QPen debugLines(QColor(200, 0, 0), 1, Qt::DashLine, Qt::SquareCap);
        painter->setPen(debugLines);
        painter->drawRect(this->getBasicRect());

        if (this->getModel<CircuitElementModel>() != nullptr) {
            QPointF center = this->getModel<CircuitElementModel>()->getCenter();
            QPoint pos = QPoint(static_cast<int>(this->pos().x() / this->cell_size.width()), static_cast<int>(this->pos().y() / this->cell_size.height()));
            painter->drawPoint(center);

            QString text = QString("(%1;%2)").arg(pos.x()).arg(pos.y());

            QFontMetrics font_metrics = painter->fontMetrics();
            QRect text_rect = font_metrics.boundingRect(text);

            QRectF text_pos_rect = QRectF(center.x() - text_rect.width() / 2, center.y() - text_rect.height(), text_rect.width(), text_rect.height());
            painter->fillRect(text_pos_rect, QColor(255, 255, 255, 200));
            painter->drawText(text_pos_rect, Qt::AlignCenter, text);
        }

        if (this->getModel<CircuitElementModel>() != nullptr) {
            int angle = this->getModel<CircuitElementModel>()->getAngle();
            QHash<QPoint, InputPointData> inputs_points = this->getModel<CircuitElementModel>()->getInputsPoints();
            for (InputPointData input_point_data : inputs_points.values()) {
                InputPointData input_point_data_rotated = input_point_data.withAngle(angle);

                painter->drawRect(input_point_data_rotated.calculateInputRect(this->cell_size, 10, 10));
            }
        }
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void CircuitElementGraphicsItem::updateDrawImage() {
    QColor color;
    if (this->mark_hovered) {
        color = this->hover_color;
    }
    else if (this->mark_selected) {
        color = this->selection_color;
    }
    else if (this->mark_collided) {
        color = this->disable_color;
    }
    else {
        color = this->color;
    }

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

void CircuitElementGraphicsItem::setCellSize(const QSizeF &cell_size)
{
    FieldGraphicsItem::setCellSize(cell_size);
    this->setPos(this->updatedPos());
}

void CircuitElementGraphicsItem::paramsUpdated()
{
    this->updateDrawImage();
    this->FieldGraphicsItem::paramsUpdated();
}

void CircuitElementGraphicsItem::setCenter(const QPoint &center)
{
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

void CircuitElementGraphicsItem::setSelectionColor(const QColor &selection_color)
{
    this->selection_color = selection_color;
    this->paramsUpdated();
}

void CircuitElementGraphicsItem::setDisableColor(const QColor &disable_color)
{
    this->disable_color = disable_color;
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




CircuitElementModel::CircuitElementModel(QObject *parent)
    : FieldElementModel(parent),
      SelectableModelComponentsKeeper()
{

    this->angle = 0;
    this->cells_rect = QRect(0, 0, 1, 1);

    this->setGraphicsItem(FieldElementModel::createGraphicsItem<CircuitElementGraphicsItem>(this));
}

CircuitElementModel::CircuitElementModel(const CircuitElementModel &obj)
    : FieldElementModel(obj),
      SelectableModelComponentsKeeper(obj)
{

    this->angle = obj.angle;
    this->cells_rect = obj.cells_rect;
    this->inputs_points = obj.inputs_points;
    this->center = obj.center;
    this->setGraphicsItem(obj.cloneGraphicsItem<CircuitElementGraphicsItem>(this));
}

CircuitElementModel::~CircuitElementModel()
{

}

