#ifndef CAPACITORPROPERTIESCOMPONENT_H
#define CAPACITORPROPERTIESCOMPONENT_H

#include "model_components/properties_components/fieldelementpropertiescomponent.h"
#include "libs/objectcounter.h"

class CapacitorPropertiesComponent : public FieldElementPropertiesComponent, public ObjectCounter<CapacitorPropertiesComponent>
{
    Q_OBJECT;
    Q_PROPERTY(double capacity MEMBER m_capacity NOTIFY capacityChanged);

private:
    double m_capacity;

public:
    explicit CapacitorPropertiesComponent(QObject *parent = nullptr);
    CapacitorPropertiesComponent(const CapacitorPropertiesComponent &obj);
    virtual BasicComponent* clone() { return new CapacitorPropertiesComponent(*this); }

    void generateComponentWidget();

    // вспомогательные методы
    virtual void installedToField() {
        ObjectCounter<CapacitorPropertiesComponent>::increaseId();
        this->setProperty("element_name", QString("C%1").arg(this->getId()));
    }

signals:
    void capacityChanged(double);
};

#endif // CAPACITORPROPERTIESCOMPONENT_H
