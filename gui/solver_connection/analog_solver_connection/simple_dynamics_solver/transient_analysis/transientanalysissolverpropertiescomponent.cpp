#include "transientanalysissolverpropertiescomponent.h"

TransientAnalysisSolverPropertiesComponent::TransientAnalysisSolverPropertiesComponent(QObject *parent)
    : SolverPropertiesComponent(parent),
    m_analysis_time(10.0),
    m_start_time_step(1e-2),
    m_max_correction_error(1e-5),
    m_max_newtons_iterations(7)
{
    this->setProperty("solver_name", "Transient analisys");
}

TransientAnalysisSolverPropertiesComponent::TransientAnalysisSolverPropertiesComponent(const TransientAnalysisSolverPropertiesComponent &obj)
    : SolverPropertiesComponent(obj),
    m_analysis_time(obj.m_analysis_time),
    m_start_time_step(obj.m_start_time_step),
    m_max_correction_error(obj.m_max_correction_error),
    m_max_newtons_iterations(obj.m_max_newtons_iterations)
{

}

void TransientAnalysisSolverPropertiesComponent::generateComponentWidget()
{
    PropertiesComponent::generateForm(QList<QMap<QString, QVariant>>(
        {
            {
                std::pair<QString, QVariant>("name", "analysis_time"),
                std::pair<QString, QVariant>("title", "Analysis time"),
                std::pair<QString, QVariant>("min", 0),
                std::pair<QString, QVariant>("max", 1000000000),
                std::pair<QString, QVariant>("decimals", 16),
            },
            {
                std::pair<QString, QVariant>("name", "start_time_step"),
                std::pair<QString, QVariant>("title", "Start time step"),
                std::pair<QString, QVariant>("min", 0),
                std::pair<QString, QVariant>("max", 1000000000),
                std::pair<QString, QVariant>("decimals", 16),
            },
            {
                std::pair<QString, QVariant>("name", "max_correction_error"),
                std::pair<QString, QVariant>("title", "Max correction error"),
                std::pair<QString, QVariant>("min", 0),
                std::pair<QString, QVariant>("max", 1000000000),
                std::pair<QString, QVariant>("decimals", 16),
            },
            {
                std::pair<QString, QVariant>("name", "max_newtons_iterations"),
                std::pair<QString, QVariant>("title", "Max newtons iterations"),
                std::pair<QString, QVariant>("min", 0),
                std::pair<QString, QVariant>("max", 1000000000),
                std::pair<QString, QVariant>("decimals", 16),
            }
        }
    ));
}
