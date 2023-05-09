#ifndef SOLVERCONNECTOR_H
#define SOLVERCONNECTOR_H

#include <QObject>
#include "solverpropertiescomponent.h"
#include "solverserializer.h"
#include "solverrunner.h"
#include "solverresult.h"

class SolverConnector : public QObject
{
    Q_OBJECT

public:
    explicit SolverConnector(QObject *parent = nullptr);
    void afterConstruct();

    SolverPropertiesComponent* getSolverPropertiesComponent() { return this->solver_properties_component; }
    SolverSerializer* getSolverSerializer() { return this->solver_serializer; }
    SolverRunner* getSolverRunner() { return this->solver_runner; }

protected:
    SolverPropertiesComponent *solver_properties_component;
    SolverSerializer *solver_serializer;
    SolverRunner *solver_runner;

public slots:
    void solve();

signals:
    void solved(const SolverResult &);
};

#endif // SOLVERCONNECTOR_H
