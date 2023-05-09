#include "capacitorpropertiescomponent.h"

template class ObjectCounter<CapacitorPropertiesComponent>;

CapacitorPropertiesComponent::CapacitorPropertiesComponent(QObject *parent)
    : FieldElementPropertiesComponent(parent),
      ObjectCounter<CapacitorPropertiesComponent>(false),
      m_capacity(1.0)
{

}

CapacitorPropertiesComponent::CapacitorPropertiesComponent(const CapacitorPropertiesComponent &obj)
    : FieldElementPropertiesComponent(obj),
      ObjectCounter<CapacitorPropertiesComponent>(false),
      m_capacity(obj.m_capacity)
{

}

void CapacitorPropertiesComponent::generateComponentWidget()
{
    FieldElementPropertiesComponent::generateForm(QList<QMap<QString, QVariant>>(
        {
            {
                std::pair<QString, QVariant>("name", "capacity"),
                std::pair<QString, QVariant>("title", "Capacity"),
            }
        }
    ));
}
