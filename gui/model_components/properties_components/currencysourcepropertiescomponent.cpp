#include "currencysourcepropertiescomponent.h"

template class ObjectCounter<CurrencySourcePropertiesComponent>;

CurrencySourcePropertiesComponent::CurrencySourcePropertiesComponent(QObject *parent)
    : FieldElementPropertiesComponent(parent),
      ObjectCounter<CurrencySourcePropertiesComponent>(false),
      m_currency(1.0)
{

}

CurrencySourcePropertiesComponent::CurrencySourcePropertiesComponent(const CurrencySourcePropertiesComponent &obj)
    : FieldElementPropertiesComponent(obj),
      ObjectCounter<CurrencySourcePropertiesComponent>(false),
      m_currency(obj.m_currency)
{

}

void CurrencySourcePropertiesComponent::generateComponentWidget()
{
    FieldElementPropertiesComponent::generateForm(QList<QMap<QString, QVariant>>(
        {
            {
                std::pair<QString, QVariant>("name", "currency"),
                std::pair<QString, QVariant>("title", "Currency"),
            }
        }
    ));
}
