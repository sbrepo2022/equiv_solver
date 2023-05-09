#include "fieldcontroller.h"
#include "../fieldstyledialog.h"
#include "../circuitsettingsdialog.h"

FieldController::FieldController(FieldView *field_view, QObject *parent) :
    QObject(parent),
    field_view(field_view),
    current_field_model_id(-1),
    cell_size(QSizeF(16, 16)),
    edit_mode_controller(nullptr)
{
    connect(this, &FieldController::gridSizeChanged, this, &FieldController::updateScene);

    registerEditModes();
}

int FieldController::addFieldModel(FieldModel *field_model)
{
    if (field_model == nullptr) return -1;

    field_model->setCellSize(this->cell_size);
    connect(this, &FieldController::cellSizeChanged, field_model, &FieldModel::setCellSize);

    // --debug--
    connect(this, &FieldController::graphicsItemDebugChanged, field_model, &FieldModel::setGraphicsItemDebug);
    // --debug--

    this->field_models.insert(field_model->getId(), field_model);
    return field_model->getId();
}

FieldModel* FieldController::removeFieldModel(int id)
{
    FieldModel *return_model = nullptr;
    if (this->field_models.contains(id)) {
        return_model = this->field_models[id];
        disconnect(this, &FieldController::cellSizeChanged, return_model, &FieldModel::setCellSize);
        this->field_models.remove(id);
    }

    if (this->field_models.count() == 0)
        this->setCurrentFieldModel(-1);

    return return_model;
}

void FieldController::setCurrentFieldModel(int id)
{
    this->detachFieldModel();

    if (this->field_models.contains(id)) {
        this->current_field_model_id = id;
        if (this->field_view != nullptr) this->field_view->setScene(this->field_models[id]->getScene());
        this->updateScene();
    }
    else {
        this->current_field_model_id = -1;
        if (this->field_view != nullptr) this->field_view->setScene(nullptr);
    }

    this->attachFieldModel();
}

FieldModel* FieldController::getCurrentFieldModel()
{
    if (this->field_models.contains(this->current_field_model_id)) {
        return this->field_models[this->current_field_model_id];
    }

    return nullptr;
}

void FieldController::registerEditModes() {
    FieldSelectModeController *field_select_edit_mode = new FieldSelectModeController(this);
    connect(field_select_edit_mode, &FieldSelectModeController::selectableModelSelected,
            this, &FieldController::selectableModelSelected);
    this->avail_edit_modes.insert(FieldEditMode::SELECT, field_select_edit_mode);

    this->avail_edit_modes.insert(FieldEditMode::WIRE, new FieldWireModeController(this));

    this->avail_edit_modes.insert(FieldEditMode::DELETE, new FieldDeleteModeController(this));

    this->avail_edit_modes.insert(FieldEditMode::DRAW_ELEMENT, new FieldDrawElementModeController(this));

    this->setSelectMode();
}

void FieldController::detachFieldModel()
{
    if (this->edit_mode_controller != nullptr) this->edit_mode_controller->detachFieldModel();
}

void FieldController::attachFieldModel()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) {
        if (this->edit_mode_controller != nullptr)this->edit_mode_controller->attachFieldModel(field_model);
    }
}

void FieldController::setSelectMode()
{
    this->detachFieldModel();
    this->edit_mode_controller = this->avail_edit_modes[FieldEditMode::SELECT];
    this->attachFieldModel();
}

void FieldController::setWireMode()
{
    this->detachFieldModel();
    this->edit_mode_controller = this->avail_edit_modes[FieldEditMode::WIRE];
    this->attachFieldModel();
}

void FieldController::setDeleteMode()
{
    this->detachFieldModel();
    this->edit_mode_controller = this->avail_edit_modes[FieldEditMode::DELETE];
    this->attachFieldModel();
}

void FieldController::setDrawElementsMode(CircuitElementModel *model)
{
    this->detachFieldModel();
    qobject_cast<FieldDrawElementModeController*>(this->avail_edit_modes[FieldEditMode::DRAW_ELEMENT])->setCircuitElement(model);
    this->edit_mode_controller = this->avail_edit_modes[FieldEditMode::DRAW_ELEMENT];
    this->attachFieldModel();
}

void FieldController::delegateActionTriggerToEditMode(QString action_name)
{
    if (this->edit_mode_controller != nullptr) {
        this->edit_mode_controller->actionTriggered(action_name);
    }
}

void FieldController::updateScene()
{
    FieldModel *field_model = this->getCurrentFieldModel();
    if (field_model != nullptr) field_model->updateScene();
}

void FieldController::showFieldSettingsDialog()
{
    FieldStyleDialog dialog(this);
    switch (dialog.exec()) {
        case QDialog::Accepted:
            this->setCellSize(dialog.getCellSize());
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
            break;

        case QDialog::Rejected:
            break;
    }
}

