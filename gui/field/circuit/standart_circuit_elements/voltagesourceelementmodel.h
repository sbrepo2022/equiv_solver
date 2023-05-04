#ifndef VOLTAGESOURCEELEMENTMODEL_H
#define VOLTAGESOURCEELEMENTMODEL_H

#include <QObject>

#include "../circuitelementmodel.h"

class VoltageSourceElementModel : public CircuitElementModel
{
    Q_OBJECT

public:
    explicit VoltageSourceElementModel(QObject *parent = nullptr);
};

#endif // VOLTAGESOURCEELEMENTMODEL_H
