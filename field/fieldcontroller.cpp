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

    this->field_models.insert(field_model->getId(), field_model);
    return field_model->getId();
}

FieldModel* FieldController::removeFieldModel(int index)
{
    FieldModel *return_model = nullptr;
    if (this->field_models.contains(index)) {
        return_model = this->field_models[index];
        this->field_models.remove(index);
    }

    if (this->field_models.count() == 0)
        this->setCurrentFieldModel(-1);

    return return_model;
}

void FieldController::setCurrentFieldModel(int index)
{
    this->detachScene();

    if (this->field_models.contains(index)) {
        this->current_field_model_ind = index;
        if (this->field_view != nullptr) this->field_view->setScene(this->field_models[index]->getScene());
        this->updateScene();
    }
    else {
        this->current_field_model_ind = -1;
        if (this->field_view != nullptr) this->field_view->setScene(nullptr);
    }

    this->attachScene();
}

FieldModel* FieldController::getCurrentFieldModel()
{
    if (this->field_models.contains(this->current_field_model_ind)) {
        return this->field_models[this->current_field_model_ind];
    }

    return nullptr;
}

void FieldController::attachScene()
{
    if (this->buffer_graphics_item != nullptr) {
        FieldModel *field_model = this->getCurrentFieldModel();
        if (field_model != nullptr) field_model->addFieldGraphicsItem(this->buffer_graphics_item);
    }
}

void FieldController::detachScene()
{
    if (this->buffer_graphics_item != nullptr) {
        FieldModel *field_model = this->getCurrentFieldModel();
        if (field_model != nullptr) field_model->removeFieldGraphicsItem(this->buffer_graphics_item);
    }
}

void FieldController::unsetEditMode()
{
    // after DRAW_ELEMENT mode
    if (this->buffer_element != nullptr) {
        delete buffer_element;
        this->buffer_element = nullptr;
    }

    this->buffer_graphics_item = nullptr;
}

void FieldController::connectWithGraphicsItem(FieldGraphicsItem *field_graphics_item) {
    connect(this, &FieldController::cellSizeChanged, field_graphics_item, &FieldGraphicsItem::setCellSize);
}

void FieldController::setSelectMode()
{
    this->edit_mode = FieldEditMode::SELECT;
}

void FieldController::setWireMode()
{
    this->edit_mode = FieldEditMode::WIRE;
}

void FieldController::setDeleteMode()
{
    this->edit_mode = FieldEditMode::DELETE;
}

void FieldController::setDrawElementsMode(CircuitElementModel *model)
{
    this->edit_mode = FieldEditMode::DRAW_ELEMENT;

    this->buffer_graphics_item = model->getGraphicsItem();
    this->buffer_element = model;
    this->buffer_graphics_item->setCellSize(this->cell_size);
    this->connectWithGraphicsItem(this->buffer_graphics_item);
    this->buffer_graphics_item->setColor(QColor(200, 20, 0));
    this->buffer_graphics_item->setVisibility(false);
}

void FieldController::updateScene()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) field_model->updateScene();
}

void FieldController::gridCellHover(const QPoint &pos)
{
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
            FieldModel *field_model = this->getCurrentFieldModel();
            CircuitElementModel *circuit_element = new CircuitElementModel(*(this->buffer_element));
            field_model->addCircuitElement(circuit_element);
            circuit_element->setCenter(pos);
            this->connectWithGraphicsItem(circuit_element->getGraphicsItem());
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
