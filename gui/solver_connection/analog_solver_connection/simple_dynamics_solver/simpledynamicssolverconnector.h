#ifndef SIMPLEDYNAMICSSOLVERCONNECTOR_H
#define SIMPLEDYNAMICSSOLVERCONNECTOR_H

#include "../../solverconnector.h"
#include "simpledynamicssolverserializer.h"
#include "simpledynamicssolverpropertiescomponent.h"
#include "simpledynamicssolverrunner.h"
#include "simpledynamicssolverresult.h"

class SimpleDynamicsSolverConnector : public SolverConnector
{
    Q_OBJECT

public:
    explicit SimpleDynamicsSolverConnector(QObject *parent = nullptr);
};

#endif // SIMPLEDYNAMICSSOLVERCONNECTOR_H
