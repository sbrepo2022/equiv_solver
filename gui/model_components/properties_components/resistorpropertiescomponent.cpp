#include "resistorpropertiescomponent.h"

template class ObjectCounter<ResistorPropertiesComponent>;

ResistorPropertiesComponent::ResistorPropertiesComponent(QObject *parent)
    : FieldElementPropertiesComponent(parent),
      ObjectCounter<ResistorPropertiesComponent>(false),
      m_resistance(1.0)
{

}

ResistorPropertiesComponent::ResistorPropertiesComponent(const ResistorPropertiesComponent &obj)
    : FieldElementPropertiesComponent(obj),
      ObjectCounter<ResistorPropertiesComponent>(false),
      m_resistance(obj.m_resistance)
{

}

void ResistorPropertiesComponent::generateComponentWidget()
{
    FieldElementPropertiesComponent::generateForm(QList<QMap<QString, QVariant>>(
        {
            {
                std::pair<QString, QVariant>("name", "resistance"),
                std::pair<QString, QVariant>("title", "Resistance"),
            }
        }
    ));
}
