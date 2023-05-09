#ifndef SELECTABLEMODELCOMPONENTSKEEPER_H
#define SELECTABLEMODELCOMPONENTSKEEPER_H

#include "properties_components/propertiescomponent.h"
#include "properties_components/fieldelementpropertiescomponent.h"

class SelectableModelComponentsKeeper
{
public:
    SelectableModelComponentsKeeper();
    SelectableModelComponentsKeeper(const SelectableModelComponentsKeeper &obj);
    ~SelectableModelComponentsKeeper();

    PropertiesComponent *getPropertiesComponent() {
        return this->properties_component;
    }

    void setPropertiesComponent(PropertiesComponent *properties_component) {
        this->properties_component = properties_component;
    }

private:
    PropertiesComponent *properties_component;
};

#endif // SELECTABLEMODELCOMPONENTSKEEPER_H
