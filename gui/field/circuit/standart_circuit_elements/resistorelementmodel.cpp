#include "resistorelementmodel.h"

ResistorElementModel::ResistorElementModel(QObject *parent)
    : CircuitElementModel(parent)
{
    this->setCellsRect(QRect(-2, -2, 4, 4));

    QHash<QPoint, InputPointData> inputs_points;
    inputs_points.insert(QPoint(-2, 0),
        InputPointData(
            QPoint(-2, 0),
            QPoint(-1, 0),
            "1"
        )
    );
    inputs_points.insert(QPoint(2, 0),
        InputPointData(
            QPoint(2, 0),
            QPoint(1, 0),
            "2"
        )
    );
    this->setInputsPoints(inputs_points);
    this->getGraphicsItem<CircuitElementGraphicsItem>()->setImage(QImage(":/circuit_icons/resources/resistor.png"));
}
