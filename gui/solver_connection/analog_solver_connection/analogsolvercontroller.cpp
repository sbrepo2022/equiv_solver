#include "analogsolvercontroller.h"

AnalogSolverController::AnalogSolverController(QObject *parent)
    : SolverController(parent)
{
    this->controller_name = QString("Analog");
}


void AnalogSolverController::registerSolvers()
{
    TransientAnalysisSolverConnector *transient_analysis_solver_connector = new TransientAnalysisSolverConnector();
    this->registered_solvers.insert(transient_analysis_solver_connector->getSolverName(), transient_analysis_solver_connector);

    SolverController::registerSolvers();
}

void AnalogSolverController::setCurrentFieldModel(FieldModel *field_model) {
    for (SolverConnector *solver_connector : this->registered_solvers) {
        TransientAnalysisSolverConnector *transient_analysis_solver_connector =
            qobject_cast<TransientAnalysisSolverConnector*>(solver_connector);

        if (transient_analysis_solver_connector != nullptr) {
            transient_analysis_solver_connector->setCurrentFieldModel(field_model);
        }
    }
}


