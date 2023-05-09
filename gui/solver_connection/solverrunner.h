#ifndef SOLVERRUNNER_H
#define SOLVERRUNNER_H

#include <QObject>
#include "solverresult.h"
#include "solverpropertiescomponent.h"

class SolverRunner : public QObject
{
    Q_OBJECT

public:
    explicit SolverRunner(QObject *parent = nullptr);

public slots:
    virtual void runSolver(QString serialized_data_filename, SolverPropertiesComponent *solver_properties_component) = 0;

signals:
    void solved(const SolverResult &);
};

#endif // SOLVERRUNNER_H
