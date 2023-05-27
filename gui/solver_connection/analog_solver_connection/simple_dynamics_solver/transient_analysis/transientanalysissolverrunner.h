#ifndef TRANSIENTANALYSISSOLVERRUNNER_H
#define TRANSIENTANALYSISSOLVERRUNNER_H

#include <QProcess>
#include <QDir>

#include "solver_connection/solverrunner.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverresult.h"
#include "filestorage.h"

class TransientAnalysisSolverRunner : public SolverRunner
{
    Q_OBJECT

public:
    explicit TransientAnalysisSolverRunner(QObject *parent = nullptr);

    QString getOutputCsvFile();

protected:
    virtual QString getRunCmd();
    virtual QStringList getProcessArguments(const QString &serialized_data_filename, SolverPropertiesComponent *solver_properties_component);

private slots:
    void onStarted();
    void onFinished(int, QProcess::ExitStatus);
    void onReadyReadStandartOutput();
};

#endif // TRANSIENTANALYSISSOLVERRUNNER_H
