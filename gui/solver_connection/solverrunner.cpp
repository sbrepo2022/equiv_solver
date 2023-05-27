#include "solverrunner.h"

SolverRunner::SolverRunner(QObject *parent)
    : QObject(parent),
      solver_process(nullptr)
{
    connect(&solver_process, &QProcess::readyReadStandardError, this, &SolverRunner::onReadyReadStandartError);
    connect(&solver_process, &QProcess::finished, this, &SolverRunner::onFinished);
}


void SolverRunner::runSolver(QString serialized_data_filename, SolverPropertiesComponent *solver_properties_component)
{
    QString cmd = this->getRunCmd();
    QStringList args = this->getProcessArguments(serialized_data_filename, solver_properties_component);

    if (this->solver_process.state() == QProcess::Running) {
        throw SolverRunningException("Solving process already running!");
    }

    this->error_message = "";
    this->solver_process.start(cmd, args);
}

void SolverRunner::onReadyReadStandartError()
{
    QByteArray error = solver_process.readAllStandardError();
    this->error_message += error.toStdString().c_str();
}

void SolverRunner::onFinished(int exit_code, QProcess::ExitStatus exit_status)
{
    if (this->error_message != "") {
        emit errorOccured(this->error_message);
    }
}
