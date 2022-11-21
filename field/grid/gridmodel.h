#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

#include "../fieldgraphicsitem.h"

class GridModel;

class GridGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit GridGraphicsItem(GridModel *model, QObject *parent = nullptr);
    ~GridGraphicsItem();

    QRectF boundingRect() const;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    GridModel *model;
    qreal line_width;
    QColor line_color;

    // events state
    QPoint last_hover_cell;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void onCellLeave(QPoint);
    void onCellEnter(QPoint);
    void onItemEnter();
    void onItemLeave();
    void onCellPressed(QPoint);

public slots:
    void setLineWidh(qreal line_width) {this->line_width = line_width;}
    void setLineColor(QColor line_color) {this->line_color = line_color;}
};


class GridModel : public QObject
{
    Q_OBJECT
public:
    explicit GridModel(QObject *parent = nullptr);
    ~GridModel();
    GridGraphicsItem* getGraphicsItem() {return this->graphics_item;}

    QSize getGridSize() {return this->grid_size;}

private:
    GridGraphicsItem* graphics_item;

    QSize grid_size;

signals:

public slots:
    void setGridSize(const QSize &grid_size) {this->grid_size = grid_size;}
};

#endif // GRIDMODEL_H
