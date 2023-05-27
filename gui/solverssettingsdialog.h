#ifndef SOLVERSSETTINGSDIALOG_H
#define SOLVERSSETTINGSDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>

#include "solverssettingstab.h"
#include "solver_connection/solverprovider.h"

namespace Ui {
class SolversSettingsDialog;
}

class SolversSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolversSettingsDialog(const QList<SolverProvider*> &solvers_providers,
                                   SolverProvider* current_solver_provider,
                                   QWidget *parent = nullptr);
    ~SolversSettingsDialog();

private:
    Ui::SolversSettingsDialog *ui;
};

#endif // SOLVERSSETTINGSDIALOG_H
