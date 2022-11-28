#include "fielddeletemodecontroller.h"

FieldDeleteModeController::FieldDeleteModeController(QObject *parent)
    : FieldSelectModeController(parent)
{

}

void FieldDeleteModeController::detachFieldModel()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        disconnect(field_model, &FieldModel::onGraphicsItemMousePressed, this, &FieldDeleteModeController::onGraphicsItemMousePressed);
    }

    this->FieldSelectModeController::detachFieldModel();
}

void FieldDeleteModeController::attachFieldModel(FieldModel *field_model)
{
    if (field_model != nullptr) {
        connect(field_model, &FieldModel::onGraphicsItemMousePressed, this, &FieldDeleteModeController::onGraphicsItemMousePressed);
    }

    this->FieldSelectModeController::attachFieldModel(field_model);
}

void FieldDeleteModeController::onGraphicsItemMousePressed(FieldGraphicsItem *graphics_item, QGraphicsSceneMouseEvent *event)
{
    qDebug() << "hello";
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model == nullptr || graphics_item == nullptr) return;

    if (event->buttons() & Qt::LeftButton) {
        FieldGraphicsItemType type = graphics_item->getType();
        if (type == FieldGraphicsItemType::CIRCUIT_ELEMENT) {
            CircuitElementModel *circuit_element = qobject_cast<CircuitElementGraphicsItem*>(graphics_item)->getModel();
            field_model->removeCircuitElement(circuit_element->getId());
            delete circuit_element;
        }
        if (type == FieldGraphicsItemType::WIRE) {
            WireModel *wire = qobject_cast<WireGraphicsItem*>(graphics_item)->getModel();
            field_model->removeCircuitElement(wire->getId());
            delete wire;
        }
    }
}
