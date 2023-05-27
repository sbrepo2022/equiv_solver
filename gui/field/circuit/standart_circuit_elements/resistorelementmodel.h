#ifndef RESISTORELEMENTMODEL_H
#define RESISTORELEMENTMODEL_H

#include <QObject>

#include "field/circuit/circuitelementmodel.h"
#include "model_components/properties_components/resistorpropertiescomponent.h"

class ResistorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit ResistorElementModel(QObject *parent = nullptr);

    virtual ResistorElementModel* copy() {
        return (new ResistorElementModel(*this));
    }
};

#endif // RESISTORELEMENTMODEL_H
