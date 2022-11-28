#include "fieldselectmodecontroller.h"

FieldSelectModeController::FieldSelectModeController(QObject *parent)
    : FieldEditModeController(parent),
      current_graphics_item(nullptr)
{

}

void FieldSelectModeController::detachFieldModel()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        disconnect(field_model, &FieldModel::onGraphicsItemEntered, this, &FieldSelectModeController::onGraphicsItemEntered);
        disconnect(field_model, &FieldModel::onGraphicsItemLeaved, this, &FieldSelectModeController::onGraphicsItemLeaved);

        field_model->setAcceptHoverEventsFromFieldElements(false);
    }

    if (this->current_graphics_item != nullptr) {
        this->current_graphics_item->setMarkHovered(false);
    }

    this->FieldEditModeController::detachFieldModel();
}

void FieldSelectModeController::attachFieldModel(FieldModel *field_model)
{
    if (field_model != nullptr) {
        connect(field_model, &FieldModel::onGraphicsItemEntered, this, &FieldSelectModeController::onGraphicsItemEntered);
        connect(field_model, &FieldModel::onGraphicsItemLeaved, this, &FieldSelectModeController::onGraphicsItemLeaved);

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
}
