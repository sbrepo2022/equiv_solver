#ifndef CURRENCYSOURCEPROPERTIESCOMPONENT_H
#define CURRENCYSOURCEPROPERTIESCOMPONENT_H

#include "model_components/properties_components/fieldelementpropertiescomponent.h"
#include "libs/objectcounter.h"

class CurrencySourcePropertiesComponent : public FieldElementPropertiesComponent, public ObjectCounter<CurrencySourcePropertiesComponent>
{
    Q_OBJECT;
    Q_PROPERTY(double currency MEMBER m_currency NOTIFY currencyChanged);

private:
    double m_currency;

public:
    explicit CurrencySourcePropertiesComponent(QObject *parent = nullptr);
    CurrencySourcePropertiesComponent(const CurrencySourcePropertiesComponent &obj);
    virtual BasicComponent* clone() { return new CurrencySourcePropertiesComponent(*this); }

    void generateComponentWidget();

    // вспомогательные методы
    virtual void installedToField() {
        ObjectCounter<CurrencySourcePropertiesComponent>::increaseId();
        this->setProperty("element_name", QString("I%1").arg(this->getId()));
    }

signals:
    void currencyChanged(double);
};

#endif // CURRENCYSOURCEPROPERTIESCOMPONENT_H
