#ifndef INDUCTORELEMENTMODEL_H
#define INDUCTORELEMENTMODEL_H

#include <QObject>

#include "field/circuit/circuitelementmodel.h"
#include "model_components/properties_components/inductorpropertiescomponent.h"

class InductorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit InductorElementModel(QObject *parent = nullptr);

    virtual InductorElementModel* copy() {
        return (new InductorElementModel(*this));
    }
};

#endif // INDUCTORELEMENTMODEL_H
