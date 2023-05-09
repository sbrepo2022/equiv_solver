#include "fieldselectmodecontroller.h"

FieldSelectModeController::FieldSelectModeController(QObject *parent)
    : FieldEditModeController(parent),
      current_graphics_item(nullptr),
      selected_graphics_item(nullptr)
{

}

void FieldSelectModeController::detachFieldModel()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        disconnect(field_model, &FieldModel::onGraphicsItemEntered, this, &FieldSelectModeController::onGraphicsItemEntered);
        disconnect(field_model, &FieldModel::onGraphicsItemLeaved, this, &FieldSelectModeController::onGraphicsItemLeaved);
        disconnect(field_model, &FieldModel::onGraphicsItemHoverMoved, this, &FieldSelectModeController::onGraphicsItemHoverMoved);
        disconnect(field_model, &FieldModel::onGraphicsItemMousePressed, this, &FieldSelectModeController::onGraphicsItemMousePressed);

        field_model->setAcceptHoverEventsFromFieldElements(false);
    }

    if (this->current_graphics_item != nullptr) {
        this->current_graphics_item->setMarkHovered(false);
    }
    this->cancelObjectSelection();

    this->clearCurrentGraphicsItem();

    this->FieldEditModeController::detachFieldModel();
}

void FieldSelectModeController::cancelObjectSelection()
{
    if (this->selected_graphics_item != nullptr) {
        this->selected_graphics_item->setMarkSelected(false);

        emit selectableModelSelected(nullptr);
    }
}

void FieldSelectModeController::attachFieldModel(FieldModel *field_model)
{
    if (field_model != nullptr) {
        connect(field_model, &FieldModel::onGraphicsItemEntered, this, &FieldSelectModeController::onGraphicsItemEntered);
        connect(field_model, &FieldModel::onGraphicsItemLeaved, this, &FieldSelectModeController::onGraphicsItemLeaved);
        connect(field_model, &FieldModel::onGraphicsItemHoverMoved, this, &FieldSelectModeController::onGraphicsItemHoverMoved);
        connect(field_model, &FieldModel::onGraphicsItemMousePressed, this, &FieldSelectModeController::onGraphicsItemMousePressed);

        field_model->setAcceptHoverEventsFromFieldElements(true);
    }

    this->FieldEditModeController::attachFieldModel(field_model);
}

void FieldSelectModeController::onGraphicsItemEntered(FieldGraphicsItem *graphics_item)
{
    this->current_graphics_item = graphics_item;

    if (graphics_item != nullptr) {
        graphics_item->setMarkHovered(true);
    }
}

void FieldSelectModeController::onGraphicsItemLeaved(FieldGraphicsItem *graphics_item)
{
    if (graphics_item != nullptr) {
        graphics_item->setMarkHovered(false);
    }

    this->current_graphics_item = nullptr;
}

void FieldSelectModeController::onGraphicsItemHoverMoved(FieldGraphicsItem *graphics_item, QGraphicsSceneHoverEvent *event)
{
    this->current_graphics_item = graphics_item;
}

void FieldSelectModeController::onGraphicsItemMousePressed(FieldGraphicsItem *graphics_item, QGraphicsSceneMouseEvent *event)
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model == nullptr || graphics_item == nullptr) return;

    if (event->buttons() & Qt::LeftButton) {
        FieldGraphicsItemType type = graphics_item->getType();
        if (type == FieldGraphicsItemType::CIRCUIT_ELEMENT && this->current_graphics_item != nullptr) {
            CircuitElementModel *circuit_element = qobject_cast<CircuitElementGraphicsItem*>(graphics_item)->getModel<CircuitElementModel>();

            this->cancelObjectSelection();

            this->selected_graphics_item = graphics_item;
            this->selected_graphics_item->setMarkSelected(true);
            emit selectableModelSelected(circuit_element);
        }
        else {
            this->cancelObjectSelection();
        }
    }
}
