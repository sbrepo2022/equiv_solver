#include "fieldmodel.h"

FieldModel::FieldModel(QObject *parent) : QObject(parent)
{
    this->scene = new QGraphicsScene();
    this->grid_model = new GridModel();
    this->grid_graphics_item = this->grid_model->createGridGraphicsItem();

    grid_graphics_item->setZValue(0);
    this->scene->addItem(grid_graphics_item);
    this->scene->setSceneRect(grid_graphics_item->boundingRect());
}

FieldModel::~FieldModel()
{
    delete this->scene;
    delete this->grid_model;
}

void FieldModel::updateScene() {
    this->scene->setSceneRect(grid_graphics_item->boundingRect());
}
