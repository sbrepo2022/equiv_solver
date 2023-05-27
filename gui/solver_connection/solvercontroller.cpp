#include "solvercontroller.h"

SolverController::SolverController(QObject *parent)
    : QObject(parent),
      controller_name("Abstract"),
      solving_now(false),
      current_solver_key("")
{

}

void SolverController::registerSolvers()
{
    if (this->registered_solvers.count() > 0) {
        this->current_solver_key = this->registered_solvers.keys()[0];
    }

    for (SolverConnector *solver_connector : this->registered_solvers) {
        solver_connector->afterConstruct();
        connect(solver_connector, &SolverConnector::errorOccured, this, &SolverController::errorOccured);
    }
}

void SolverController::solve()
{
    try {
        if (!this->current_solver_key.isEmpty() && !this->solving_now) {
            this->solving_now = true;
            connect(this->registered_solvers[this->current_solver_key], &SolverConnector::solved, this, &SolverController::onSolved);
            this->registered_solvers[this->current_solver_key]->solve();
        }
    }
    catch (const SerializationException &e) {
        this->solving_now = false;
        emit errorOccured(e.what());
    }
    catch (const SolverRunningException &e) {
        this->solving_now = false;
        emit errorOccured(e.what());
    }
}

void SolverController::onSolved(const SolverResult &result)
{
    this->solving_now = false;
    disconnect(this->registered_solvers[this->current_solver_key], &SolverConnector::solved, this, &SolverController::onSolved);
    emit solved(result);
}


bool SolverController::setCurrentSolver(QString key)
{
    if (this->registered_solvers.contains(key) && !this->solving_now) {
        this->current_solver_key = key;
        return true;
    }
    return false;
}
