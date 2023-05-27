#include "currencysourceelementmodel.h"

CurrencySourceElementModel::CurrencySourceElementModel(QObject *parent)
    : CircuitElementModel (parent)
{
    this->setMeta(CircuitElementModelMeta("CurrencySource"));

    this->setCellsRect(QRect(-2, -2, 4, 4));

    QHash<QPoint, InputPointData> inputs_points;
    inputs_points.insert(QPoint(0, 2),
        InputPointData(
            0,
            QPoint(0, 2),
            QPoint(0, 1),
            "-"
        )
    );
    inputs_points.insert(QPoint(0, -2),
        InputPointData(
            1,
            QPoint(0, -2),
            QPoint(0, -1),
            "+"
        )
    );
    this->setInputsPoints(inputs_points);
    this->getGraphicsItem<CircuitElementGraphicsItem>()->setImage(QImage(":/circuit_icons/resources/current.png"));

    // init selectable model components keeper
    CurrencySourcePropertiesComponent *currency_source_properties_component = new CurrencySourcePropertiesComponent();
    this->setPropertiesComponent(currency_source_properties_component);
}
