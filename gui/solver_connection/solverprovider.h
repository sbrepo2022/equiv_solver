#ifndef SOLVERPROVIDER_H
#define SOLVERPROVIDER_H

#include "solver_connection/solvercontroller.h"

class SolverProvider
{
public:
    SolverProvider();

    virtual SolverController* getSolverController() = 0;
};

#endif // SOLVERPROVIDER_H
