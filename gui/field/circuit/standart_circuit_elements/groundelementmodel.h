#ifndef GROUNDELEMENTMODEL_H
#define GROUNDELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"

class GroundElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit GroundElementModel(QObject *parent = nullptr);
};

#endif // GROUNDELEMENTMODEL_H
