#ifndef SIMPLEDYNAMICSSOLVERSERIALIZER_H
#define SIMPLEDYNAMICSSOLVERSERIALIZER_H

#include "../../solverserializer.h"

class SimpleDynamicsSolverSerializer : public SolverSerializer
{
    Q_OBJECT
public:
    explicit SimpleDynamicsSolverSerializer(QObject *parent = nullptr);
};

#endif // SIMPLEDYNAMICSSOLVERSERIALIZER_H
