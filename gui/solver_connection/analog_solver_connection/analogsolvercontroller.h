#ifndef ANALOGSOLVERCONTROLLER_H
#define ANALOGSOLVERCONTROLLER_H

#include "field/fieldmodel.h"
#include "solver_connection/solvercontroller.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverconnector.h"

class AnalogSolverController : public SolverController
{
    Q_OBJECT

public:
    explicit AnalogSolverController(QObject *parent = nullptr);

    void setCurrentFieldModel(FieldModel *field_model);

protected:
    virtual void registerSolvers();
};

#endif // ANALOGSOLVERCONTROLLER_H
