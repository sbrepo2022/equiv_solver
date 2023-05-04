#ifndef CAPACITORELEMENTMODEL_H
#define CAPACITORELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"

class CapacitorElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit CapacitorElementModel(QObject *parent = nullptr);
};

#endif // CAPACITORELEMENTMODEL_H
