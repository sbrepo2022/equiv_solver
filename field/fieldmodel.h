#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QObject>
#include <QGraphicsScene>

#include "grid/gridmodel.h"
#include "circuit/circuitelementmodel.h"

class FieldModel : public QObject
{
    Q_OBJECT
public:
    explicit FieldModel(QObject *parent = nullptr);
    ~FieldModel();

    QGraphicsScene* getScene() {return this->scene;}

    QSize getGridSize() {return this->grid_model->getGridSize();}
    void setGridSize(const QSize &grid_size) {this->grid_model->setGridSize(grid_size);}

    GridGraphicsItem* getGridGraphicsItem() {return this->grid_graphics_item;}

private:
    QGraphicsScene *scene;
    GridModel *grid_model;
    GridGraphicsItem *grid_graphics_item;
    QList <CircuitElementModel*> circuit_elements;

public slots:
    void updateScene();
};

#endif // FIELDMODEL_H
