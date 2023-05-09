#ifndef RESISTORPROPERTIESCOMPONENT_H
#define RESISTORPROPERTIESCOMPONENT_H

#include "fieldelementpropertiescomponent.h"
#include "../../libs/objectcounter.h"

class ResistorPropertiesComponent : public FieldElementPropertiesComponent, public ObjectCounter<ResistorPropertiesComponent>
{
    Q_OBJECT;
    Q_PROPERTY(double resistance MEMBER m_resistance NOTIFY resistanceChanged);

private:
    double m_resistance;

public:
    explicit ResistorPropertiesComponent(QObject *parent = nullptr);
    ResistorPropertiesComponent(const ResistorPropertiesComponent &obj);
    virtual BasicComponent* clone() { return new ResistorPropertiesComponent(*this); }

    void generateComponentWidget();

    // вспомогательные методы
    virtual void installedToField() {
        ObjectCounter<ResistorPropertiesComponent>::increaseId();
        this->setProperty("element_name", QString("R%1").arg(this->getId()));
    }

signals:
    void resistanceChanged(double);
};

#endif // RESISTORPROPERTIESCOMPONENT_H
