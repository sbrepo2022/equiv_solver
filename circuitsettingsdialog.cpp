#include "circuitsettingsdialog.h"
#include "ui_circuitsettingsdialog.h"

CircuitSettingsDialog::CircuitSettingsDialog(FieldController *field_controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CircuitSettingsDialog),
    field_controller(field_controller)
{
    ui->setupUi(this);

    if (field_controller != nullptr) {
        ui->fieldWidth->setValue(field_controller->getGridSize().width());
        ui->fieldHeight->setValue(field_controller->getGridSize().height());
    }
}

CircuitSettingsDialog::~CircuitSettingsDialog()
{
    delete ui;
}

QSize CircuitSettingsDialog::getGridSize()
{
    return QSize(this->ui->fieldWidth->value(), this->ui->fieldHeight->value());
}
