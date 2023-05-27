#include "solverpropertiescomponent.h"

SolverPropertiesComponent::SolverPropertiesComponent(QObject *parent)
    : PropertiesComponent(parent),
    m_solver_name("")
{

}

SolverPropertiesComponent::SolverPropertiesComponent(const SolverPropertiesComponent &obj)
    : PropertiesComponent(obj),
      m_solver_name(obj.m_solver_name)
{

}

