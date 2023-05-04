#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

#include "../fieldelementmodel.h"
#include "../../libs/objectcounter.h"

class GridModel;

class GridGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit GridGraphicsItem(QObject *parent = nullptr);
    GridGraphicsItem(const GridGraphicsItem &obj);
    ~GridGraphicsItem();
    FieldGraphicsItemType getType() {return FieldGraphicsItemType::GRID;}

    QRectF boundingRect() const;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal line_width;
    QColor line_color;

    // events state
    QPoint last_hover_cell;

    void init();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPoint getCellByMousePos(const QPointF &pos);

signals:
    void onCellLeave(QPoint);
    void onCellEnter(QPoint);
    void onItemEnter();
    void onItemLeave();
    void onCellPressed(QPoint);

public slots:
    virtual void attachFieldElementModel();
    virtual void detachFieldElementModel();
    void setLineWidth(qreal line_width) {this->line_width = line_width;}
    void setLineColor(QColor line_color) {this->line_color = line_color;}
};


class GridModel : public FieldElementModel
{
    Q_OBJECT
public:
    explicit GridModel(QObject *parent = nullptr);
    GridModel(const GridModel &obj);
    ~GridModel();

    QSize getGridSize() {return this->grid_size;}

private:
    QSize grid_size;

signals:

public slots:
    void setGridSize(const QSize &grid_size) {this->grid_size = grid_size;}
};

#endif // GRIDMODEL_H
