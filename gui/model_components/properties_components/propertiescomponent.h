#ifndef PROPERTIESCOMPONENT_H
#define PROPERTIESCOMPONENT_H

#include <QWidget>
#include <QFormLayout>

#include "../widgetcomponent.h"
#include "../../libs/formgenerator.h"

class PropertiesComponent : public WidgetComponent
{
    Q_OBJECT;

public:
    explicit PropertiesComponent(QObject *parent = nullptr);
    PropertiesComponent(const PropertiesComponent &obj);

protected:
    // Метод generateForm используется для генерации стандартной формы с параметрами
    // Создан для вызова в унаследованной реализации метода generateInterfaceWidget
    void generateForm(const QList<QMap<QString, QVariant>> &widget_properties);

private:
    FormGenerator form_generator;
};

#endif // PROPERTIESCOMPONENT_H
