#include "fielddeletemodecontroller.h"

FieldDeleteModeController::FieldDeleteModeController(QObject *parent)
    : FieldEditModeController(parent)
{

}

void FieldDeleteModeController::detachFieldModel()
{

    this->FieldEditModeController::detachFieldModel();
}

void FieldDeleteModeController::attachFieldModel(FieldModel *field_model)
{

    this->FieldEditModeController::attachFieldModel(field_model);
}
