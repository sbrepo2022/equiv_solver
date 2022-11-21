#ifndef FIELDSTYLEDIALOG_H
#define FIELDSTYLEDIALOG_H

#include <QDialog>

#include "field/fieldcontroller.h"

namespace Ui {
class FieldStyleDialog;
}

class FieldStyleDialog : public QDialog
{
    Q_OBJECT

public:
    FieldStyleDialog(FieldController *field_controller, QWidget *parent = nullptr);
    ~FieldStyleDialog();

    QSizeF getCellSize();

private:
    Ui::FieldStyleDialog *ui;
    FieldController *field_controller;
};

#endif // FIELDSTYLEDIALOG_H
