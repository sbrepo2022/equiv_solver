#ifndef SOLVERCONTROLLER_H
#define SOLVERCONTROLLER_H

#include <QObject>
#include <QMap>

#include "solver_connection/solverconnector.h"
#include "solver_connection/solverresult.h"

class SolverController : public QObject
{
    Q_OBJECT

public:
    explicit SolverController(QObject *parent = nullptr);
    void init() {
        this->registerSolvers();
    }

    QString getControllerName() {
        return this->controller_name;
    }

    const QMap<QString, SolverConnector*> getRegisteredSolvers() {
        return this->registered_solvers;
    }

    QString getCurrentSolverKey() {
        return this->current_solver_key;
    }

    SolverConnector* getCurrentSolver() {
        return this->registered_solvers[this->current_solver_key];
    }

    bool setCurrentSolver(QString key);

protected:
    virtual void registerSolvers();

    QString controller_name;
    bool solving_now;

    QString current_solver_key;
    QMap<QString, SolverConnector*> registered_solvers;

protected slots:
    void onSolved(const SolverResult &);

public slots:
    void solve();

signals:
    void solved(const SolverResult &);
    void errorOccured(const QString &);
};

#endif // SOLVERCONTROLLER_H
