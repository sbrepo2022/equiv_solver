#include "simpledynamicssolverconnector.h"

SimpleDynamicsSolverConnector::SimpleDynamicsSolverConnector(QObject *parent)
    : SolverConnector(parent)
{
    this->solver_serializer = new SimpleDynamicsSolverSerializer();
    this->solver_properties_component = new SimpleDynamicsSolverPropertiesComponent();
    this->solver_runner = new SimpleDynamicsSolverRunner();
    this->solver_result = new SimpleDynamicsSolverResult();
}
