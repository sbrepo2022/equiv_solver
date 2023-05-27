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
    connect(this->solver_runner, &SolverRunner::errorOccured, this, &SolverConnector::errorOccured);
}

QString SolverConnector::getSolverName() {
    if (this->solver_properties_component == nullptr) return QString();

    return this->solver_properties_component->property("solver_name").toString();
}

void SolverConnector::solve()
{
    if (this->solver_serializer == nullptr || this->solver_runner == nullptr || this->solver_properties_component == nullptr) return;

    QString serialized_data_filename = this->solver_serializer->serialize();
    this->solver_runner->runSolver(serialized_data_filename, this->solver_properties_component);
}
