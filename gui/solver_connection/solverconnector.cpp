#include "solverconnector.h"

SolverConnector::SolverConnector(QObject *parent)
    : QObject(parent),
      solver_properties_component(nullptr),
      solver_serializer(nullptr),
      solver_runner(nullptr)
{

}

void SolverConnector::afterConstruct()
{
    if (this->solver_runner == nullptr) return;
    connect(this->solver_runner, &SolverRunner::solved, this, &SolverConnector::solved);
}

void SolverConnector::solve()
{
    if (this->solver_serializer == nullptr || this->solver_runner == nullptr || this->solver_properties_component == nullptr) return;

    QString serialized_data_filename = this->solver_serializer->serialize();
    this->solver_runner->runSolver(serialized_data_filename, this->solver_properties_component);
}
