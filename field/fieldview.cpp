#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent)
{
    this->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
    this->setScene(nullptr);
}

FieldView::~FieldView()
{

}
/*
void FieldView::addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item) {
    if (this->scene() != nullptr) {
        field_graphics_item->setZValue(100);
        this->scene()->addItem(field_graphics_item);
    }
}

void FieldView::removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item) {
    if (this->scene() != nullptr) {
        this->scene()->removeItem(field_graphics_item);
    }
}
*/
