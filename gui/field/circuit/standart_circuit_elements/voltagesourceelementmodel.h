#ifndef VOLTAGESOURCEELEMENTMODEL_H
#define VOLTAGESOURCEELEMENTMODEL_H

#include <QObject>

#include "field/circuit/circuitelementmodel.h"
#include "model_components/properties_components/voltagesourcepropertiescomponent.h"

class VoltageSourceElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit VoltageSourceElementModel(QObject *parent = nullptr);

    virtual VoltageSourceElementModel* copy() {
        return (new VoltageSourceElementModel(*this));
    }
};

#endif // VOLTAGESOURCEELEMENTMODEL_H
