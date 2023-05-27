#ifndef TRANSIENTANALYSISSOLVERRESULT_H
#define TRANSIENTANALYSISSOLVERRESULT_H

#include <QFile>

#include "solver_connection/solverresult.h"

class TransientAnalysisSolverResult : public SolverResult
{
    Q_OBJECT

public:
    explicit TransientAnalysisSolverResult(QObject *parent = nullptr);

    void setCSVResultFile(const QString &result_file) { this->result_file = result_file; }

    virtual void loadResult();
    virtual QList<QLineSeries*> getLineSeries() const { return this->line_series; }

private:
    QString result_file;
    QList<QLineSeries*> line_series;

    QList<QLineSeries*> readDataFromCSV();
};

#endif // TRANSIENTANALYSISSOLVERRESULT_H
