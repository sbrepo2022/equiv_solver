#ifndef FIELDELEMENTPROPERTIESCOMPONENT_H
#define FIELDELEMENTPROPERTIESCOMPONENT_H

#include "model_components/properties_components/propertiescomponent.h"

class FieldElementPropertiesComponent : public PropertiesComponent
{
    Q_OBJECT;
    Q_PROPERTY(QString element_name MEMBER m_element_name NOTIFY elementNameChanged);

private:
    QString m_element_name;

public:
    explicit FieldElementPropertiesComponent(QObject *parent = nullptr);
    FieldElementPropertiesComponent(const FieldElementPropertiesComponent &obj);

    // вспомогательные методы
    virtual void installedToField() {}

protected:
    // Метод generateForm используется для генерации стандартной формы с параметрами
    // Создан для вызова в унаследованной реализации метода generateInterfaceWidget
    void generateForm(const QList<QMap<QString, QVariant>> &widget_properties);

signals:
    void elementNameChanged(double);
};

#endif // FIELDELEMENTPROPERTIESCOMPONENT_H
