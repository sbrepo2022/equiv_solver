#include "fieldmodel.h"

int FieldModel::object_count = 0;

FieldModel::FieldModel(QObject *parent) : QObject(parent)
{
    id = FieldModel::object_count++;

    this->scene = new QGraphicsScene();
    this->grid_model = new GridModel();
    this->grid_graphics_item = this->grid_model->getGraphicsItem();

    grid_graphics_item->setZValue(0);
    this->scene->addItem(grid_graphics_item);
    this->scene->setSceneRect(grid_graphics_item->boundingRect());
}

FieldModel::~FieldModel()
{
    this->scene->removeItem(grid_graphics_item);

    delete this->scene;
    delete this->grid_model;
}

void FieldModel::updateScene() {
    this->scene->setSceneRect(grid_graphics_item->boundingRect());
}

void FieldModel::addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item)
{
    if (this->scene != nullptr) {
        field_graphics_item->setZValue(100);
        this->scene->addItem(field_graphics_item);
    }
}

void FieldModel::removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item)
{
    if (this->scene != nullptr) {
        this->scene->removeItem(field_graphics_item);
    }
}

void FieldModel::addCircuitElement(CircuitElementModel *circuit_element)
{
    CircuitElementGraphicsItem *graphics_item = circuit_element->getGraphicsItem();
    graphics_item->setColor(QColor(0, 0, 0));
    this->circuit_elements.insert(circuit_element->getId(), circuit_element);
    if (this->scene != nullptr) {
        graphics_item->setZValue(50);
        this->scene->addItem(graphics_item);
    }
}
