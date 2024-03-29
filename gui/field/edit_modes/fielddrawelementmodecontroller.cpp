#include "fielddrawelementmodecontroller.h"

FieldDrawElementModeController::FieldDrawElementModeController(QObject *parent)
    : FieldEditModeController(parent),
      buffer_element(nullptr),
      buffer_graphics_item(nullptr),
      buffer_element_collided(false)
{

}

void FieldDrawElementModeController::detachFieldModel()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        disconnect(field_model, &FieldModel::onCellEnter, this, &FieldDrawElementModeController::gridCellHover);
        disconnect(field_model, &FieldModel::onGridEnter, this, &FieldDrawElementModeController::gridItemEnter);
        disconnect(field_model, &FieldModel::onGridLeave, this, &FieldDrawElementModeController::gridItemLeave);
        disconnect(field_model, &FieldModel::onCellPressed, this, &FieldDrawElementModeController::gridCellPressed);

        if (this->buffer_graphics_item != nullptr) {
            field_model->removeFieldGraphicsItem(this->buffer_graphics_item);
        }
    }

    this->FieldEditModeController::detachFieldModel();
}

void FieldDrawElementModeController::attachFieldModel(FieldModel *field_model)
{
    if (field_model != nullptr)  {
        connect(field_model, &FieldModel::onCellEnter, this, &FieldDrawElementModeController::gridCellHover);
        connect(field_model, &FieldModel::onGridEnter, this, &FieldDrawElementModeController::gridItemEnter);
        connect(field_model, &FieldModel::onGridLeave, this, &FieldDrawElementModeController::gridItemLeave);
        connect(field_model, &FieldModel::onCellPressed, this, &FieldDrawElementModeController::gridCellPressed);

        if (this->buffer_graphics_item != nullptr) {
            field_model->addFieldGraphicsItem(this->buffer_graphics_item, 100);
        }
    }

    this->FieldEditModeController::attachFieldModel(field_model);
}

void FieldDrawElementModeController::actionTriggered(QString action_name)
{
    if (action_name == "RotateElementRight") {
        if (this->buffer_element != nullptr) {
            this->buffer_element->rotateRight();
        }
    }
    if (action_name == "RotateElementLeft") {
        if (this->buffer_element != nullptr) {
            this->buffer_element->rotateLeft();
        }
    }

    FieldEditModeController::actionTriggered(action_name);
}

void FieldDrawElementModeController::setCircuitElement(CircuitElementModel *circuit_model) {
    if (this->buffer_element != nullptr) {
        delete buffer_element;
        this->buffer_element = nullptr;
    }
    this->buffer_graphics_item = nullptr;

    this->buffer_graphics_item = circuit_model->getGraphicsItem<CircuitElementGraphicsItem>();
    this->buffer_element = circuit_model;
    this->buffer_graphics_item->setColor(QColor(200, 20, 0));
    this->buffer_graphics_item->setVisibility(false);
}

void FieldDrawElementModeController::gridCellHover(const QPoint &pos)
{
    if (this->buffer_graphics_item != nullptr) {
        this->buffer_element->setCenter(pos);
        this->buffer_graphics_item->setVisibility(true);

        FieldModel *field_model = this->getCurrentFieldModel();
        if (field_model != nullptr) {
            QGraphicsScene *scene = field_model->getScene();
            if (scene != nullptr) {
                this->buffer_element_collided = field_model->checkItemCollision(this->buffer_graphics_item, scene);
                this->buffer_graphics_item->setMarkCollided(this->buffer_element_collided);
            }

            field_model->updateScene();
        }
    }
}

void FieldDrawElementModeController::gridItemEnter()
{
    if (this->buffer_graphics_item != nullptr) {
        this->buffer_graphics_item->setVisibility(true);
    }
}

void FieldDrawElementModeController::gridItemLeave()
{
    if (this->buffer_graphics_item != nullptr) {
        this->buffer_graphics_item->setVisibility(false);
    }
}

void FieldDrawElementModeController::gridCellPressed(const QPoint &pos)
{
    if (this->buffer_element_collided) return;

    if (this->buffer_element == nullptr) return;

    if (this->buffer_graphics_item != nullptr) {
        this->buffer_graphics_item->setCenter(pos);
        this->buffer_graphics_item->setVisibility(true);
    }

    CircuitElementModel *circuit_element = this->buffer_element->copy();
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) field_model->addCircuitElement(circuit_element);
}
