#include "selectablemodelview.h"

SelectableModelView::SelectableModelView(
    QWidget *properties_view_widget,
    QObject *parent
) : QObject(parent),
    properties_view_widget(properties_view_widget)
{

}

void SelectableModelView::removeAllWidgetsFromLayout(QLayout *layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void SelectableModelView::onSelectableModelSelected(SelectableModelComponentsKeeper *components_keeper)
{
    if (components_keeper == nullptr) {
        this->hidePropertiesView();
    }
    else {
        this->showPropertiesView(components_keeper->getPropertiesComponent());
    }
}

void SelectableModelView::showPropertiesView(PropertiesComponent *properties_component)
{
    if (properties_component == nullptr) return;
    properties_component->init();
    QWidget *properties_component_widget = properties_component->getComponentWidget();

    if (this->properties_view_widget->layout() != nullptr) {
        SelectableModelView::removeAllWidgetsFromLayout(this->properties_view_widget->layout());
        this->properties_view_widget->layout()->addWidget(properties_component_widget);
    }
}

void SelectableModelView::hidePropertiesView()
{
    if (this->properties_view_widget->layout() != nullptr) {
        SelectableModelView::removeAllWidgetsFromLayout(this->properties_view_widget->layout());
    }
}
