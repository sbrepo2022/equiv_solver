#ifndef CURRENCYSOURCEELEMENTMODEL_H
#define CURRENCYSOURCEELEMENTMODEL_H

#include <QObject>

#include "field/circuit/circuitelementmodel.h"
#include "model_components/properties_components/currencysourcepropertiescomponent.h"

class CurrencySourceElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit CurrencySourceElementModel(QObject *parent = nullptr);

    virtual CurrencySourceElementModel* copy() {
        return (new CurrencySourceElementModel(*this));
    }
};

#endif // CURRENCYSOURCEELEMENTMODEL_H
