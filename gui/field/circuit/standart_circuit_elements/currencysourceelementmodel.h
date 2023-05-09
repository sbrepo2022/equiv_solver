#ifndef CURRENCYSOURCEELEMENTMODEL_H
#define CURRENCYSOURCEELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"
#include "../../../model_components/properties_components/currencysourcepropertiescomponent.h"

class CurrencySourceElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit CurrencySourceElementModel(QObject *parent = nullptr);
};

#endif // CURRENCYSOURCEELEMENTMODEL_H
