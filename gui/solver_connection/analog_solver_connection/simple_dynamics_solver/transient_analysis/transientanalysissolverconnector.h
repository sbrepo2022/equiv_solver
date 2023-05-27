#ifndef TRANSIENTANALYSISSOLVERCONNECTOR_H
#define TRANSIENTANALYSISSOLVERCONNECTOR_H

#include "solver_connection/solverconnector.h"
#include "field/fieldmodel.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverserializer.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverpropertiescomponent.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverrunner.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverresult.h"

class TransientAnalysisSolverConnector : public SolverConnector
{
    Q_OBJECT

public:
    explicit TransientAnalysisSolverConnector(QObject *parent = nullptr);

    void setCurrentFieldModel(FieldModel *field_model);
};

#endif // TRANSIENTANALYSISSOLVERCONNECTOR_H
