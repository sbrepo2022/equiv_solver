#include "selectablemodelcomponentskeeper.h"

SelectableModelComponentsKeeper::SelectableModelComponentsKeeper()
    : properties_component(nullptr)
{

}

SelectableModelComponentsKeeper::SelectableModelComponentsKeeper(const SelectableModelComponentsKeeper &obj)
    : properties_component(nullptr)
{
    if (obj.properties_component != nullptr)
        this->properties_component = qobject_cast<PropertiesComponent*>(obj.properties_component->clone());
}

SelectableModelComponentsKeeper::~SelectableModelComponentsKeeper()
{
    if (this->properties_component != nullptr) delete this->properties_component;
}
