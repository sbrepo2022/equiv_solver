#include "fieldelementpropertiescomponent.h"

FieldElementPropertiesComponent::FieldElementPropertiesComponent(QObject *parent)
    : PropertiesComponent(parent)
{

}

FieldElementPropertiesComponent::FieldElementPropertiesComponent(const FieldElementPropertiesComponent &obj)
    : PropertiesComponent(obj),
      m_element_name(obj.m_element_name)
{

}

void FieldElementPropertiesComponent::generateForm(const QList<QMap<QString, QVariant>> &widget_properties)
{
    QList<QMap<QString, QVariant>> widget_properties_with_base = {
        {
            std::pair<QString, QVariant>("name", "element_name"),
            std::pair<QString, QVariant>("title", "Element name"),
            std::pair<QString, QVariant>("field_type", "line"),
        }
    };
    widget_properties_with_base.append(widget_properties);

    PropertiesComponent::generateForm(widget_properties_with_base);
}
