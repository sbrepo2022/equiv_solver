#include "inductorelementmodel.h"

InductorElementModel::InductorElementModel(QObject *parent)
    : CircuitElementModel(parent)
{
    this->setMeta(CircuitElementModelMeta("Inductor"));

    this->setCellsRect(QRect(-2, -2, 4, 4));

    QHash<QPoint, InputPointData> inputs_points;
    inputs_points.insert(QPoint(-2, 0),
        InputPointData(
            0,
            QPoint(-2, 0),
            QPoint(-1, 0),
            "pin_0"
        )
    );
    inputs_points.insert(QPoint(2, 0),
        InputPointData(
            1,
            QPoint(2, 0),
            QPoint(1, 0),
            "pin_1"
        )
    );
    this->setInputsPoints(inputs_points);
    this->getGraphicsItem<CircuitElementGraphicsItem>()->setImage(QImage(":/circuit_icons/resources/inductor.png"));

    // init selectable model components keeper
    InductorPropertiesComponent *inductor_properties_component = new InductorPropertiesComponent();
    this->setPropertiesComponent(inductor_properties_component);
}
