#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent), scene(nullptr), grid_graphics_item(nullptr)
{
    this->scene = new QGraphicsScene();
    this->setScene(scene);

    this->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
}

FieldView::~FieldView()
{

}

void FieldView::setGridGraphicsItem(GridGraphicsItem *grid_graphics_item) {
    if (this->grid_graphics_item != nullptr) {
        this->scene->removeItem(this->grid_graphics_item);
        this->grid_graphics_item->deleteLater();
    }

    grid_graphics_item->setZValue(0);
    this->scene->addItem(grid_graphics_item);
    this->scene->setSceneRect(grid_graphics_item->boundingRect());

    this->grid_graphics_item = grid_graphics_item;
}

void FieldView::addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item) {
    field_graphics_item->setZValue(100);
    this->scene->addItem(field_graphics_item);
}

void FieldView::removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item) {
    this->scene->removeItem(field_graphics_item);
}
