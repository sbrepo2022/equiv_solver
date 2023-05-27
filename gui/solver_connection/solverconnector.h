#ifndef SOLVERCONNECTOR_H
#define SOLVERCONNECTOR_H

#include <QObject>
#include "solver_connection/solverpropertiescomponent.h"
#include "solver_connection/solverserializer.h"
#include "solver_connection/solverrunner.h"
#include "solver_connection/solverresult.h"

class SolverConnector : public QObject
{
    Q_OBJECT

public:
    explicit SolverConnector(QObject *parent = nullptr);
    void afterConstruct();

    SolverPropertiesComponent* getSolverPropertiesComponent() { return this->solver_properties_component; }
    SolverSerializer* getSolverSerializer() { return this->solver_serializer; }
    SolverRunner* getSolverRunner() { return this->solver_runner; }

    QString getSolverName();

protected:
    SolverPropertiesComponent *solver_properties_component;
    SolverSerializer *solver_serializer;
    SolverRunner *solver_runner;

public slots:
    void solve();

signals:
    void solved(const SolverResult &);
    void errorOccured(const QString &);
};

#endif // SOLVERCONNECTOR_H
