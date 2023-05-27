#include "transientanalysissolverconnector.h"

TransientAnalysisSolverConnector::TransientAnalysisSolverConnector(QObject *parent)
    : SolverConnector(parent)
{
    TransientAnalysisSolverPropertiesComponent *solver_properties_component = new TransientAnalysisSolverPropertiesComponent();
    this->solver_properties_component = solver_properties_component;

    TransientAnalysisSolverSerializer *solver_serializer = new TransientAnalysisSolverSerializer();
    this->solver_serializer = solver_serializer;

    TransientAnalysisSolverRunner *solver_runner = new TransientAnalysisSolverRunner();
    this->solver_runner = solver_runner;

    solver_serializer->setTransientAnalysisSolverPropertiesComponent(solver_properties_component);
}

void TransientAnalysisSolverConnector::setCurrentFieldModel(FieldModel *field_model)
{
    TransientAnalysisSolverSerializer *serializer = qobject_cast<TransientAnalysisSolverSerializer*>(this->getSolverSerializer());
    serializer->setCurrentFieldModel(field_model);
}
