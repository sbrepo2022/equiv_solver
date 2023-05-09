#include "propertiescomponent.h"

PropertiesComponent::PropertiesComponent(QObject *parent)
    : WidgetComponent(parent)
{

}

PropertiesComponent::PropertiesComponent(const PropertiesComponent &obj)
    : WidgetComponent(obj)
{

}

void PropertiesComponent::generateForm(const QList<QMap<QString, QVariant>> &widget_properties)
{
    QWidget *component_widget = new QWidget();
    QVBoxLayout *widget_layout = new QVBoxLayout(component_widget);
    widget_layout->setContentsMargins(0, 0, 0, 0);

    QWidget *form_widget = new QWidget();
    QFormLayout *form_layout = new QFormLayout(form_widget);
    form_layout->setContentsMargins(0, 0, 0, 0);

    widget_layout->addWidget(form_widget);

    this->form_generator.generateForm(form_widget, form_layout, widget_properties, this);

    this->setComponentWidget(component_widget);
}
