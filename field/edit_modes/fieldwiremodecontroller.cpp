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
    this->buffer_wire->setCenter(pos);
    QVector<QPoint> points = {this->buffer_wire->convertPointToLocal(pos)};
    this->buffer_wire->setPoints(QPolygon(points));

    this->buffer_wire_graphics_item = this->buffer_wire->getGraphicsItem();
    this->buffer_wire_graphics_item->setLineColor(QColor(200, 20, 0));

    field_model->addFieldGraphicsItem(this->buffer_wire_graphics_item, 100);

    this->wire_started = true;
}

void FieldWireModeController::finishWire()
{
    FieldModel *field_model = this->getCurrentFieldModel();

    if (field_model != nullptr && this->buffer_wire != nullptr) {
        field_model->addWireElement(new WireModel(*(this->buffer_wire)));
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


void FieldWireModeController::gridCellHover(const QPoint &pos)
{
    if (!this->wire_started || this->buffer_wire == nullptr) return;

    QPolygon points = this->buffer_wire->getPoints();
    QPolygon result;

    if (points.count() == 0) return;

    QPoint pos_local = this->buffer_wire->convertPointToLocal(pos);

    if (points[0].x() == pos_local.x() || points[0].y() == pos_local.y()) {
        result.append(points[0]);
        result.append(pos_local);
    }
    else if (points.count() == 1) {
        result.append(points[0]);
        result.append(QPoint(pos_local.x(), points[0].y()));
        result.append(pos_local);
    }
    else if (points.count() > 1) {
        result.append(points[0]);
        if (points[0].x() == points[1].x()) {
            result.append(QPoint(points[0].x(), pos_local.y()));
        }
        else {
            result.append(QPoint(pos_local.x(), points[0].y()));
        }
        result.append(pos_local);
    }

    this->buffer_wire->setPoints(result);

    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) field_model->updateScene();
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
