#ifndef INDUCTORPROPERTIESCOMPONENT_H
#define INDUCTORPROPERTIESCOMPONENT_H

#include "model_components/properties_components/fieldelementpropertiescomponent.h"
#include "libs/objectcounter.h"

class InductorPropertiesComponent : public FieldElementPropertiesComponent, public ObjectCounter<InductorPropertiesComponent>
{
    Q_OBJECT;
    Q_PROPERTY(double induction MEMBER m_induction NOTIFY inductionChanged);

private:
    double m_induction;

public:
    explicit InductorPropertiesComponent(QObject *parent = nullptr);
    InductorPropertiesComponent(const InductorPropertiesComponent &obj);
    virtual BasicComponent* clone() { return new InductorPropertiesComponent(*this); }

    void generateComponentWidget();

    // вспомогательные методы
    virtual void installedToField() {
        ObjectCounter<InductorPropertiesComponent>::increaseId();
        this->setProperty("element_name", QString("L%1").arg(this->getId()));
    }

signals:
    void inductionChanged(double);
};

#endif // INDUCTORPROPERTIESCOMPONENT_H
