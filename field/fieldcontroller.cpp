#include "fieldcontroller.h"
#include "../fieldstyledialog.h"
#include "../circuitsettingsdialog.h"

FieldController::FieldController(FieldView *field_view, QObject *parent) :
    QObject(parent),
    field_view(field_view),
    current_field_model_ind(-1),
    cell_size(QSizeF(64, 64)),
    buffer_element(nullptr),
    buffer_graphics_item(nullptr)
{
    connect(this, &FieldController::cellSizeChanged, this, &FieldController::updateScene);
    connect(this, &FieldController::gridSizeChanged, this, &FieldController::updateScene);
}

int FieldController::addFieldModel(FieldModel *field_model)
{
    GridGraphicsItem *grid_graphics_item = field_model->getGridGraphicsItem();
    grid_graphics_item->setCellSize(this->cell_size);
    this->connectWithGraphicsItem(grid_graphics_item);

    connect(grid_graphics_item, &GridGraphicsItem::onCellEnter, this, &FieldController::gridCellHover);
    connect(grid_graphics_item, &GridGraphicsItem::onItemEnter, this, &FieldController::gridItemEnter);
    connect(grid_graphics_item, &GridGraphicsItem::onItemLeave, this, &FieldController::gridItemLeave);
    connect(grid_graphics_item, &GridGraphicsItem::onCellPressed, this, &FieldController::gridCellPressed);

    this->field_models.push_back(field_model);
    return field_models.count() - 1;
}

FieldModel* FieldController::removeFieldModel(int index)
{

}

void FieldController::setCurrentFieldModel(int index)
{
    if (index >= 0 && index < this->field_models.count()) {
        this->current_field_model_ind = index;
        if (this->field_view != nullptr) this->field_view->setScene(this->field_models[index]->getScene());
        this->updateScene();
    }
    else {
        this->current_field_model_ind = -1;
        if (this->field_view != nullptr) this->field_view->setScene(nullptr);
    }
}

void FieldController::setSelectMode()
{
    this->cleanLastModeEffects();

    this->edit_mode = FieldEditMode::SELECT;
}

void FieldController::setWireMode()
{
    this->cleanLastModeEffects();

    this->edit_mode = FieldEditMode::WIRE;
}

void FieldController::setDeleteMode()
{
    this->cleanLastModeEffects();

    this->edit_mode = FieldEditMode::DELETE;
}

void FieldController::setDrawElementsMode(CircuitElementModel *model, CircuitElementGraphicsItem *graphics_item) {
    this->cleanLastModeEffects();

    this->edit_mode = FieldEditMode::DRAW_ELEMENT;

    this->buffer_graphics_item = graphics_item;
    this->buffer_element = model;

    this->buffer_graphics_item->setCellSize(this->cell_size);
    this->connectWithGraphicsItem(this->buffer_graphics_item);
    this->buffer_graphics_item->setColor(QColor(200, 20, 0));
    this->field_view->addFieldGraphicsItem(this->buffer_graphics_item);
    this->buffer_graphics_item->setVisibility(false);
}

void FieldController::connectWithGraphicsItem(FieldGraphicsItem *field_graphics_item) {
    connect(this, &FieldController::cellSizeChanged, field_graphics_item, &FieldGraphicsItem::setCellSize);
}

void FieldController::cleanLastModeEffects()
{
    // after DRAW_ELEMENT mode
    if (this->buffer_graphics_item != nullptr) {
        this->field_view->removeFieldGraphicsItem(this->buffer_graphics_item);
        delete this->buffer_graphics_item;
        this->buffer_graphics_item = nullptr;
    }

    if (this->buffer_element != nullptr) {
        delete buffer_element;
        this->buffer_element = nullptr;
    }
}

void FieldController::updateScene()
{
    if (this->current_field_model_ind >= 0) this->field_models[this->current_field_model_ind]->updateScene();
}

void FieldController::gridCellHover(const QPoint &pos) {
    if (this->edit_mode == FieldEditMode::DRAW_ELEMENT) {
        if (this->buffer_graphics_item != nullptr) {
            this->buffer_graphics_item->setCenter(pos);
            this->buffer_graphics_item->setVisibility(true);
        }
    }
}

void FieldController::gridItemEnter()
{
    if (this->edit_mode == FieldEditMode::DRAW_ELEMENT) {
        if (this->buffer_graphics_item != nullptr) {
            this->buffer_graphics_item->setVisibility(true);
        }
    }
}

void FieldController::gridItemLeave()
{
    if (this->edit_mode == FieldEditMode::DRAW_ELEMENT) {
        if (this->buffer_graphics_item != nullptr) {
            this->buffer_graphics_item->setVisibility(false);
        }
    }
}

void FieldController::gridCellPressed(const QPoint &pos)
{
    if (this->edit_mode == FieldEditMode::DRAW_ELEMENT) {
        if (this->buffer_element != nullptr) {
            // write there cloning buffer into field
        }
    }
}

void FieldController::showFieldSettingsDialog()
{
    FieldStyleDialog dialog(this);
    switch (dialog.exec()) {
        case QDialog::Accepted:
            this->setCellSize(dialog.getCellSize());
            emit cellSizeChanged(dialog.getCellSize());
            break;

        case QDialog::Rejected:
            break;
    }
}

void FieldController::showCircuitSettingsDialog()
{
    CircuitSettingsDialog dialog(this);
    switch (dialog.exec()) {
        case QDialog::Accepted:
            this->setGridSize(dialog.getGridSize());
            emit gridSizeChanged(dialog.getGridSize());
            break;

        case QDialog::Rejected:
            break;
    }
}
