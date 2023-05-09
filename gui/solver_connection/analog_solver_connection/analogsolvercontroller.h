#ifndef ANALOGSOLVERCONTROLLER_H
#define ANALOGSOLVERCONTROLLER_H

#include "../solvercontroller.h"

class AnalogSolverController : public SolverController
{
    Q_OBJECT

public:
    explicit AnalogSolverController(QObject *parent = nullptr);

protected:
    virtual void registerSolvers();

public slots:
    virtual void solve();
};

#endif // ANALOGSOLVERCONTROLLER_H
