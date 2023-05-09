#include "widgetcomponent.h"

WidgetComponent::WidgetComponent(QObject *parent)
    : BasicComponent(parent),
      component_widget(nullptr)
{

}

WidgetComponent::WidgetComponent(const WidgetComponent &obj)
    : BasicComponent(obj),
      component_widget(nullptr)
{

}

void WidgetComponent::init()
{
    this->generateComponentWidget();
}
