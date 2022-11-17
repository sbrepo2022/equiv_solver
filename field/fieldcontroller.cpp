#include "fieldcontroller.h"

FieldController::FieldController(FieldView *field_view, QObject *parent) :
    QObject(parent),
    field_view(field_view),
    cell_size(QSizeF(64, 64)),
    buffer_element(nullptr),
    buffer_graphics_item(nullptr)
{
    GridGraphicsItem *grid_graphics_item = grid_model.createGridGraphicsItem();
    grid_graphics_item->setCellSize(this->cell_size);
    field_view->setGridGraphicsItem(grid_graphics_item);
}

void FieldController::setDrawElementsMode(CircuitElementModel *model, CircuitElementGraphicsItem *graphics_item) {
    this->edit_mode = FieldEditMode::DRAW_ELEMENT;

    if (this->buffer_graphics_item != nullptr) {
        this->field_view->removeFieldGraphicsItem(this->buffer_graphics_item);
        delete this->buffer_graphics_item;
    }

    if (this->buffer_element != nullptr) {
        delete buffer_element;
    }

    this->buffer_graphics_item = graphics_item;
    this->buffer_element = model;

    this->buffer_graphics_item->setCellSize(this->cell_size);
    this->buffer_graphics_item->setCenter(QPoint(1, 1));
    this->field_view->addFieldGraphicsItem(this->buffer_graphics_item);
}
