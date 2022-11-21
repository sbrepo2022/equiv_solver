#ifndef CIRCUITSETTINGSDIALOG_H
#define CIRCUITSETTINGSDIALOG_H

#include <QDialog>

#include "field/fieldcontroller.h"

namespace Ui {
class CircuitSettingsDialog;
}

class CircuitSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CircuitSettingsDialog(FieldController *field_controller, QWidget *parent = nullptr);
    ~CircuitSettingsDialog();

    QSize getGridSize();

private:
    Ui::CircuitSettingsDialog *ui;
    FieldController *field_controller;
};

#endif // CIRCUITSETTINGSDIALOG_H
