#include "fieldview.h"

FieldView::FieldView(QWidget *parent) : QGraphicsView(parent)
{
    this->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
    this->setScene(nullptr);
}

FieldView::~FieldView()
{

}

