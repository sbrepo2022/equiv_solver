#ifndef WIDGETCOMPONENT_H
#define WIDGETCOMPONENT_H

#include <QWidget>

#include "model_components/basiccomponent.h"

class WidgetComponent : public BasicComponent
{
    Q_OBJECT

public:
    explicit WidgetComponent(QObject *parent = nullptr);
    WidgetComponent(const WidgetComponent &obj);

    void init();

    QWidget* getComponentWidget() { return this->component_widget; }

protected:
    // Метод должен быть переопределен для создания произвольного виджета с отображением параметров.
    // В методе должен реализовываться собственный алгоритм создания виджета.
    virtual void generateComponentWidget() = 0;

    void setComponentWidget(QWidget *component_widget) { this->component_widget = component_widget; }

private:
    QWidget *component_widget;
};

#endif // WIDGETCOMPONENT_H
