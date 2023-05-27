#include "solverssettingsdialog.h"
#include "ui_solverssettingsdialog.h"

SolversSettingsDialog::SolversSettingsDialog(const QList<SolverProvider*> &solvers_providers,
                                             SolverProvider* current_solver_provider,
                                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolversSettingsDialog)
{
    ui->setupUi(this);

    for (SolverProvider *solver_provider : solvers_providers) {
        SolverController *solver_controller = solver_provider->getSolverController();
        SolversSettingsTab *page_tab = new SolversSettingsTab(solver_controller);
        ui->tabWidget->addTab(page_tab, solver_controller->getControllerName());
    }
}

SolversSettingsDialog::~SolversSettingsDialog()
{
    delete ui;
}
