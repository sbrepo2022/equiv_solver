#ifndef GRIDGRAPHICSITEM_H
#define GRIDGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include "../fieldgraphicsitem.h"
#include "gridmodel.h"

class GridGraphicsItem : public FieldGraphicsItem, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit GridGraphicsItem(QObject *parent = nullptr);
    ~GridGraphicsItem();

private:
    int width, height;
    double cellWidth, cellHeight;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public slots:
    void setWidth(int width) {this->width = width;}
    void setHeight(int height) {this->height = height;}
    void setCellWidth(double cellWidth) {this->cellWidth = cellWidth;}
    void setCellHeight(double cellHeight) {this->cellHeight = cellHeight;}
};

#endif // GRIDGRAPHICSITEM_H
