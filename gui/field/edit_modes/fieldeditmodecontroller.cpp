#include "fieldeditmodecontroller.h"

FieldEditModeController::FieldEditModeController(QObject *parent)
    : QObject(parent),
    field_model(nullptr)
{

}

void FieldEditModeController::detachFieldModel()
{
    this->field_model = nullptr;
}

void FieldEditModeController::attachFieldModel(FieldModel *field_model)
{
    this->field_model = field_model;
}

void FieldEditModeController::actionTriggered(QString action_name)
{

}
