#include "fieldselectmodecontroller.h"

FieldSelectModeController::FieldSelectModeController(QObject *parent)
    : FieldEditModeController(parent)
{

}

void FieldSelectModeController::detachFieldModel()
{

    this->FieldEditModeController::detachFieldModel();
}

void FieldSelectModeController::attachFieldModel(FieldModel *field_model)
{

    this->FieldEditModeController::attachFieldModel(field_model);
}
