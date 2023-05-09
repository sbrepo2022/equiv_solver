#include "solvercontroller.h"

SolverController::SolverController(QObject *parent)
    : QObject(parent),
      solving_now(false),
      current_solver(nullptr)
{

}

void SolverController::solve()
{
    if (this->current_solver != nullptr && !this->solving_now) {
        this->solving_now = true;
        connect(current_solver, &SolverConnector::solved, this, &SolverController::onSolved);
        current_solver->solve();
    }
}

void SolverController::onSolved(const SolverResult &)
{
    this->solving_now = false;
    disconnect(current_solver, &SolverConnector::solved, this, &SolverController::onSolved);
}
