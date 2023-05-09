#ifndef RESISTORELEMENTMODEL_H
#define RESISTORELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"
#include "../../../model_components/properties_components/resistorpropertiescomponent.h"

class ResistorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit ResistorElementModel(QObject *parent = nullptr);
};

#endif // RESISTORELEMENTMODEL_H
