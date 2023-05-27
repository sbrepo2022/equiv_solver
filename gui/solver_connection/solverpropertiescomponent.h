#ifndef SOLVERPROPERTIESCOMPONENT_H
#define SOLVERPROPERTIESCOMPONENT_H

#include "model_components/properties_components/propertiescomponent.h"

class SolverPropertiesComponent : public PropertiesComponent
{
    Q_OBJECT
    Q_PROPERTY(QString solver_name MEMBER m_solver_name NOTIFY solverNameChanged);

private:
    QString m_solver_name;

public:
    explicit SolverPropertiesComponent(QObject *parent = nullptr);
    SolverPropertiesComponent(const SolverPropertiesComponent &obj);

signals:
    void solverNameChanged(const QString &);
};

#endif // SOLVERPROPERTIESCOMPONENT_H
