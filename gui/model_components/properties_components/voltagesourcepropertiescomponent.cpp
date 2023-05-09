#include "voltagesourcepropertiescomponent.h"

template class ObjectCounter<VoltageSourcePropertiesComponent>;

VoltageSourcePropertiesComponent::VoltageSourcePropertiesComponent(QObject *parent)
    : FieldElementPropertiesComponent(parent),
      ObjectCounter<VoltageSourcePropertiesComponent>(false),
      m_voltage(1.0)
{

}

VoltageSourcePropertiesComponent::VoltageSourcePropertiesComponent(const VoltageSourcePropertiesComponent &obj)
    : FieldElementPropertiesComponent(obj),
      ObjectCounter<VoltageSourcePropertiesComponent>(false),
      m_voltage(obj.m_voltage)
{

}

void VoltageSourcePropertiesComponent::generateComponentWidget()
{
    FieldElementPropertiesComponent::generateForm(QList<QMap<QString, QVariant>>(
        {
            {
                std::pair<QString, QVariant>("name", "voltage"),
                std::pair<QString, QVariant>("title", "Voltage"),
            }
        }
    ));
}

