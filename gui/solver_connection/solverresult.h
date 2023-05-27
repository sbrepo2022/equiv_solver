#ifndef SOLVERRESULT_H
#define SOLVERRESULT_H

#include <QObject>
#include <QtCharts/QLineSeries>
#include "solver_connection/solverpropertiescomponent.h"


class SolverResult : public QObject
{
    Q_OBJECT

public:
    explicit SolverResult(QObject *parent = nullptr);

    virtual void loadResult() = 0;
    virtual QList<QLineSeries*> getLineSeries() const = 0;

    bool doneOk() const { return this->done_ok; }
    void setDoneOk(bool done_ok) { this->done_ok = done_ok; }

private:
    bool done_ok;
};

#endif // SOLVERRESULT_H
