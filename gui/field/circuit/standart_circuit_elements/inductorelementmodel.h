#ifndef INDUCTORELEMENTMODEL_H
#define INDUCTORELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"
#include "../../../model_components/properties_components/inductorpropertiescomponent.h"

class InductorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit InductorElementModel(QObject *parent = nullptr);
};

#endif // INDUCTORELEMENTMODEL_H
