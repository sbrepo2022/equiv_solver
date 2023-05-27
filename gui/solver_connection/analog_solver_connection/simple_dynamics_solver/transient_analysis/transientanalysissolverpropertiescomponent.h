#ifndef TRANSIENTANALYSISSOLVERPROPERTIESCOMPONENT_H
#define TRANSIENTANALYSISSOLVERPROPERTIESCOMPONENT_H

#include "solver_connection/solverpropertiescomponent.h"

class TransientAnalysisSolverPropertiesComponent : public SolverPropertiesComponent
{
    Q_OBJECT
    Q_PROPERTY(double analysis_time MEMBER m_analysis_time NOTIFY analysisTimeChanged);
    Q_PROPERTY(double start_time_step MEMBER m_start_time_step NOTIFY startTimeStepChanged);
    Q_PROPERTY(double max_correction_error MEMBER m_max_correction_error NOTIFY maxCorrectionErrorChanged);
    Q_PROPERTY(int max_newtons_iterations MEMBER m_max_newtons_iterations NOTIFY maxNewtonsIterationsChanged);

private:
    double m_analysis_time;
    double m_start_time_step;
    double m_max_correction_error;
    int m_max_newtons_iterations;

public:
    explicit TransientAnalysisSolverPropertiesComponent(QObject *parent = nullptr);
    TransientAnalysisSolverPropertiesComponent(const TransientAnalysisSolverPropertiesComponent &obj);
    virtual BasicComponent* clone() { return new TransientAnalysisSolverPropertiesComponent(*this); }

protected:
    void generateComponentWidget();

signals:
    void analysisTimeChanged(double);
    void startTimeStepChanged(double);
    void maxCorrectionErrorChanged(double);
    void maxNewtonsIterationsChanged(int);
};

#endif // TRANSIENTANALYSISSOLVERPROPERTIESCOMPONENT_H
