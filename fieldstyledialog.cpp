#include "fieldstyledialog.h"
#include "ui_fieldstyledialog.h"

FieldStyleDialog::FieldStyleDialog(FieldController *field_controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FieldStyleDialog),
    field_controller(field_controller)
{
    ui->setupUi(this);

    if (field_controller != nullptr) {
        ui->cellWidth->setValue(field_controller->getCellSize().width());
        ui->cellHeight->setValue(field_controller->getCellSize().height());
    }
}

FieldStyleDialog::~FieldStyleDialog()
{
    delete ui;
}

QSizeF FieldStyleDialog::getCellSize()
{
    return QSizeF(this->ui->cellWidth->value(), this->ui->cellHeight->value());
}
