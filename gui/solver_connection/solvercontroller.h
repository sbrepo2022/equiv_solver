#ifndef SOLVERCONTROLLER_H
#define SOLVERCONTROLLER_H

#include <QObject>
#include <QMap>

#include "solverconnector.h"
#include "solverresult.h"

class SolverController : public QObject
{
    Q_OBJECT

public:
    explicit SolverController(QObject *parent = nullptr);

protected:
    virtual void registerSolvers() = 0;

    bool solving_now;

    SolverConnector *current_solver;
    QMap<QString, SolverConnector*> registered_solvers;

protected slots:
    void onSolved(const SolverResult &);

public slots:
    void solve();

signals:
    void solved(const SolverResult &);
};

#endif // SOLVERCONTROLLER_H
