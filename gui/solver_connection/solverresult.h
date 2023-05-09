#ifndef SOLVERRESULT_H
#define SOLVERRESULT_H

#include <QObject>
#include "solverpropertiescomponent.h"


class SolverResult : public QObject
{
    Q_OBJECT

public:
    explicit SolverResult(QObject *parent = nullptr);

    void setSolverPropertiesComponent(SolverPropertiesComponent *solver_properties_component) {
        this->solver_properties_component = solver_properties_component;
    }

    SolverPropertiesComponent* getSolverPropertiesComponent() {
        return this->solver_properties_component;
    }

protected:
    SolverPropertiesComponent *solver_properties_component;
};

#endif // SOLVERRESULT_H
