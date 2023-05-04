#include "currencysourceelementmodel.h"

CurrencySourceElementModel::CurrencySourceElementModel(QObject *parent)
    : CircuitElementModel (parent)
{
    this->setCellsRect(QRect(-2, -2, 4, 4));

    QHash<QPoint, InputPointData> inputs_points;
    inputs_points.insert(QPoint(0, -2),
        InputPointData(
            QPoint(0, -2),
            QPoint(0, -1),
            "-"
        )
    );
    inputs_points.insert(QPoint(0, 2),
        InputPointData(
            QPoint(0, 2),
            QPoint(0, 1),
            "+"
        )
    );
    this->setInputsPoints(inputs_points);

    this->getGraphicsItem<CircuitElementGraphicsItem>()->setImage(QImage(":/circuit_icons/resources/current.png"));
}
