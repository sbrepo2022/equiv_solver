#ifndef GROUNDELEMENTMODEL_H
#define GROUNDELEMENTMODEL_H

#include <QObject>

#include "field/circuit/circuitelementmodel.h"

class GroundElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit GroundElementModel(QObject *parent = nullptr);

    virtual GroundElementModel* copy() {
        return (new GroundElementModel(*this));
    }
};

#endif // GROUNDELEMENTMODEL_H
