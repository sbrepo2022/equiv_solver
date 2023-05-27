#include "fieldwiremodecontroller.h"

FieldWireModeController::FieldWireModeController(QObject *parent)
    : FieldEditModeController(parent),
      buffer_wire(nullptr),
      buffer_wire_graphics_item(nullptr),
      wire_started(false)
{

}

void FieldWireModeController::detachFieldModel()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        disconnect(field_model, &FieldModel::onCellEnter, this, &FieldWireModeController::gridCellHover);
        disconnect(field_model, &FieldModel::onGridEnter, this, &FieldWireModeController::gridItemEnter);
        disconnect(field_model, &FieldModel::onGridLeave, this, &FieldWireModeController::gridItemLeave);
        disconnect(field_model, &FieldModel::onCellPressed, this, &FieldWireModeController::gridCellPressed);
    }

    this->clearBufferWire();

    this->FieldEditModeController::detachFieldModel();
}

void FieldWireModeController::attachFieldModel(FieldModel *field_model)
{
    if (field_model != nullptr) {
        connect(field_model, &FieldModel::onCellEnter, this, &FieldWireModeController::gridCellHover);
        connect(field_model, &FieldModel::onGridEnter, this, &FieldWireModeController::gridItemEnter);
        connect(field_model, &FieldModel::onGridLeave, this, &FieldWireModeController::gridItemLeave);
        connect(field_model, &FieldModel::onCellPressed, this, &FieldWireModeController::gridCellPressed);
    }

    this->FieldEditModeController::attachFieldModel(field_model);
}


void FieldWireModeController::startWire(const QPoint &pos)
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model == nullptr) return;

    this->buffer_wire = new WireModel();
    QPoint point = pos;
    QList<QLine> lines_list;
    lines_list << QLine(point, point);
    this->buffer_wire->setLinesList(lines_list);

    this->buffer_wire_graphics_item = this->buffer_wire->getGraphicsItem<WireGraphicsItem>();
    this->buffer_wire_graphics_item->setLineColor(QColor(200, 20, 0));

    field_model->addFieldGraphicsItem(this->buffer_wire_graphics_item, 100);

    this->wire_started = true;
}

void FieldWireModeController::finishWire()
{
    if (this->buffer_element_collided) return;

    FieldModel *field_model = this->getCurrentFieldModel();

    if (field_model != nullptr && this->buffer_wire != nullptr) {
        field_model->addWireElementWithMerge(this->buffer_wire->copy());
    }

    this->clearBufferWire();
}

void FieldWireModeController::clearBufferWire()
{
    FieldModel *field_model = this->getCurrentFieldModel();

    if (field_model != nullptr && this->buffer_wire_graphics_item != nullptr) {
        field_model->removeFieldGraphicsItem(this->buffer_wire_graphics_item);
    }

    if (this->buffer_wire != nullptr) {
        delete this->buffer_wire;
    }
    this->buffer_wire = nullptr;
    this->buffer_wire_graphics_item = nullptr;

    this->wire_started = false;
}

bool FieldWireModeController::checkIsAllCollidedItemsIsWire(const QList<QGraphicsItem*> &colliding_items)
{
    for (int i = 0; i < colliding_items.count(); i++) {
        WireGraphicsItem *wire_graphics_item = dynamic_cast<WireGraphicsItem*>(colliding_items[i]);
        if (wire_graphics_item == nullptr) return false;
    }
    return true;
}


void FieldWireModeController::gridCellHover(const QPoint &pos)
{
    if (!this->wire_started || this->buffer_wire == nullptr) return;

    QList<QLine> lines_list = this->buffer_wire->getLinesList();
    QList<QLine> result;

    if (lines_list.count() < 1) return;

    QPoint pos_local = pos;

    if (lines_list[0].p1().x() == pos_local.x() || lines_list[0].p1().y() == pos_local.y()) {
        result.append(QLine(lines_list[0].p1(), pos_local));
    }
    else if (lines_list[0].p1() == lines_list[0].p2()) {
        QPoint corner_point = QPoint(pos_local.x(), lines_list[0].p1().y());
        result.append(QLine(lines_list[0].p1(), corner_point));
        result.append(QLine(corner_point, pos_local));
    }
    else {
        QPoint corner_point;
        if (lines_list[0].p1().x() == lines_list[0].p2().x()) {
            corner_point = QPoint(lines_list[0].p1().x(), pos_local.y());
        }
        else {
            corner_point = QPoint(pos_local.x(), lines_list[0].p1().y());
        }
        result.append(QLine(lines_list[0].p1(), corner_point));
        result.append(QLine(corner_point, pos_local));
    }

    this->buffer_wire->setLinesList(result);

    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        QGraphicsScene *scene = field_model->getScene();
        if (scene != nullptr) {
            QList<QGraphicsItem*> colliding_items;
            field_model->checkItemCollision(this->buffer_wire_graphics_item, scene, &colliding_items);
            this->buffer_element_collided = !this->checkIsAllCollidedItemsIsWire(colliding_items);
            this->buffer_wire_graphics_item->setMarkCollided(this->buffer_element_collided);
        }
        field_model->updateScene();
    }
}

void FieldWireModeController::gridItemEnter()
{

}

void FieldWireModeController::gridItemLeave()
{

}

void FieldWireModeController::gridCellPressed(const QPoint &pos)
{
    if (this->wire_started) {
        this->finishWire();
    }
    else {
        this->startWire(pos);
    }
}
