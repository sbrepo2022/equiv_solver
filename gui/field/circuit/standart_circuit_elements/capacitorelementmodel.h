#ifndef CAPACITORELEMENTMODEL_H
#define CAPACITORELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"
#include "../../../model_components/properties_components/capacitorpropertiescomponent.h"

class CapacitorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit CapacitorElementModel(QObject *parent = nullptr);
};

#endif // CAPACITORELEMENTMODEL_H
