#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QObject>
#include <QMap>
#include <QGraphicsScene>

#include "grid/gridmodel.h"
#include "circuit/circuitelementmodel.h"

class FieldModel : public QObject
{
    Q_OBJECT
public:
    explicit FieldModel(QObject *parent = nullptr);
    ~FieldModel();

    int getId() {return this->id;}
    QGraphicsScene* getScene() {return this->scene;}

    QSize getGridSize() {return this->grid_model->getGridSize();}
    void setGridSize(const QSize &grid_size) {this->grid_model->setGridSize(grid_size);}

    GridGraphicsItem* getGridGraphicsItem() {return this->grid_graphics_item;}

    void addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);
    void removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);

    void addCircuitElement(CircuitElementModel *circuit_element);

private:
    static int object_count;

    int id;
    QGraphicsScene *scene;
    GridModel *grid_model;
    GridGraphicsItem *grid_graphics_item;
    QMap <int, CircuitElementModel*> circuit_elements;

public slots:
    void updateScene();
};

#endif // FIELDMODEL_H
