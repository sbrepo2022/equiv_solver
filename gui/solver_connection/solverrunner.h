#ifndef SOLVERRUNNER_H
#define SOLVERRUNNER_H

#include <QObject>
#include <QProcess>

#include "solver_connection/solverresult.h"
#include "solver_connection/solverpropertiescomponent.h"

class SolverRunningException : std::exception {
public:
    SolverRunningException(const char* message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message;
    }

private:
    const char* m_message;
};


class SolverRunner : public QObject
{
    Q_OBJECT

public:
    explicit SolverRunner(QObject *parent = nullptr);

    void runSolver(QString serialized_data_filename, SolverPropertiesComponent *solver_properties_component);

protected:
    QProcess solver_process;
    QString error_message;

    virtual QString getRunCmd() = 0;
    virtual QStringList getProcessArguments(const QString &serialized_data_filename, SolverPropertiesComponent *solver_properties_component) = 0;

signals:
    void solved(const SolverResult &);
    void errorOccured(const QString &);

private slots:
    void onFinished(int, QProcess::ExitStatus);
    void onReadyReadStandartError();
};

#endif // SOLVERRUNNER_H
