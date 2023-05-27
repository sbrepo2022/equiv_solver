#include "transientanalysissolverrunner.h"

TransientAnalysisSolverRunner::TransientAnalysisSolverRunner(QObject *parent) : SolverRunner(parent)
{
    connect(&solver_process, &QProcess::finished, this, &TransientAnalysisSolverRunner::onFinished);
    connect(&solver_process, &QProcess::started, this, &TransientAnalysisSolverRunner::onStarted);
    connect(&solver_process, &QProcess::readyReadStandardOutput, this, &TransientAnalysisSolverRunner::onReadyReadStandartOutput);
}

QString TransientAnalysisSolverRunner::getOutputCsvFile() {
    QDir tmp_dir = FileStorage::tmpDir();
    QString file_path = tmp_dir.filePath("solution_result.csv");
    return file_path;
}

QString TransientAnalysisSolverRunner::getRunCmd()
{
    return QString("../solvers/analog_solvers/transient_analysis/TransientAnalysis.exe");
}

QStringList TransientAnalysisSolverRunner::getProcessArguments(const QString &serialized_data_filename, SolverPropertiesComponent *solver_properties_component)
{
    QStringList args;
    args << serialized_data_filename << this->getOutputCsvFile();
    return args;
}

void TransientAnalysisSolverRunner::onStarted()
{

}

void TransientAnalysisSolverRunner::onFinished(int exit_code, QProcess::ExitStatus exit_status)
{
    TransientAnalysisSolverResult result;

    if (exit_status == QProcess::NormalExit) {
        result.setCSVResultFile(this->getOutputCsvFile());
        result.loadResult();

        result.setDoneOk(true);
    }
    else {
        result.setDoneOk(false);
    }

    emit solved(result);
}

void TransientAnalysisSolverRunner::onReadyReadStandartOutput()
{
    QByteArray output = solver_process.readAllStandardOutput();
    qDebug() << "Transient analysis output: " << output.toStdString().c_str();
}
