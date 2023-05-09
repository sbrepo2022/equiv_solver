#ifndef SIMPLEDYNAMICSSOLVERRESULT_H
#define SIMPLEDYNAMICSSOLVERRESULT_H

#include "../../solverresult.h"

class SimpleDynamicsSolverResult : public SolverResult
{
    Q_OBJECT

public:
    explicit SimpleDynamicsSolverResult(QObject *parent = nullptr);
};

#endif // SIMPLEDYNAMICSSOLVERRESULT_H
