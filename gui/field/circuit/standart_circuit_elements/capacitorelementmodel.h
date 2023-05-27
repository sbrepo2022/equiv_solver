#ifndef CAPACITORELEMENTMODEL_H
#define CAPACITORELEMENTMODEL_H

#include <QObject>

#include "field/circuit/circuitelementmodel.h"
#include "model_components/properties_components/capacitorpropertiescomponent.h"

class CapacitorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit CapacitorElementModel(QObject *parent = nullptr);

    virtual CapacitorElementModel* copy() {
        return (new CapacitorElementModel(*this));
    }
};

#endif // CAPACITORELEMENTMODEL_H
