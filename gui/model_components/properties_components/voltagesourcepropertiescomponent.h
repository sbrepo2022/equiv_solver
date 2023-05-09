#ifndef VOLTAGESOURCEPROPERTIESCOMPONENT_H
#define VOLTAGESOURCEPROPERTIESCOMPONENT_H

#include "fieldelementpropertiescomponent.h"
#include "../../libs/objectcounter.h"

class VoltageSourcePropertiesComponent : public FieldElementPropertiesComponent, public ObjectCounter<VoltageSourcePropertiesComponent>
{
    Q_OBJECT;
    Q_PROPERTY(double voltage MEMBER m_voltage NOTIFY voltageChanged);

private:
    double m_voltage;

public:
    explicit VoltageSourcePropertiesComponent(QObject *parent = nullptr);
    VoltageSourcePropertiesComponent(const VoltageSourcePropertiesComponent &obj);
    virtual BasicComponent* clone() { return new VoltageSourcePropertiesComponent(*this); }

    void generateComponentWidget();

    // вспомогательные методы
    virtual void installedToField() {
        ObjectCounter<VoltageSourcePropertiesComponent>::increaseId();
        this->setProperty("element_name", QString("E%1").arg(this->getId()));
    }

signals:
    void voltageChanged(double);
};

#endif // VOLTAGESOURCEPROPERTIESCOMPONENT_H
