#ifndef SIMPLEDYNAMICSSOLVERRUNNER_H
#define SIMPLEDYNAMICSSOLVERRUNNER_H

#include "../../solverrunner.h"

class SimpleDynamicsSolverRunner : public SolverRunner
{
    Q_OBJECT
public:
    explicit SimpleDynamicsSolverRunner(QObject *parent = nullptr);
};

#endif // SIMPLEDYNAMICSSOLVERRUNNER_H
