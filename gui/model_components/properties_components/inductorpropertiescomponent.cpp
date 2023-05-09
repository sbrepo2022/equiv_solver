#include "inductorpropertiescomponent.h"

template class ObjectCounter<InductorPropertiesComponent>;

InductorPropertiesComponent::InductorPropertiesComponent(QObject *parent)
    : FieldElementPropertiesComponent(parent),
      ObjectCounter<InductorPropertiesComponent>(false),
      m_induction(1.0)
{

}

InductorPropertiesComponent::InductorPropertiesComponent(const InductorPropertiesComponent &obj)
    : FieldElementPropertiesComponent(obj),
      ObjectCounter<InductorPropertiesComponent>(false),
      m_induction(obj.m_induction)
{

}

void InductorPropertiesComponent::generateComponentWidget()
{
    FieldElementPropertiesComponent::generateForm(QList<QMap<QString, QVariant>>(
        {
            {
                std::pair<QString, QVariant>("name", "induction"),
                std::pair<QString, QVariant>("title", "induction"),
            }
        }
    ));
}
