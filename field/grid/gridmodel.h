#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include "../fieldgraphicsitem.h"

class GridModel;

class GridGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit GridGraphicsItem(GridModel *model, QObject *parent = nullptr);
    ~GridGraphicsItem();

    QRectF boundingRect() const;

private:
    GridModel *model;
    qreal line_width;
    QColor line_color;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void setLineWidh(qreal line_width) {this->line_width = line_width;}
    void setLineColor(QColor line_color) {this->line_color = line_color;}
};


class GridModel : public QObject
{
    Q_OBJECT
public:
    explicit GridModel(QObject *parent = nullptr);
    GridGraphicsItem* createGridGraphicsItem();

    int getWidth() {return this->width;}
    int getHeight() {return this->height;}

private:
    int width;
    int height;

signals:

public slots:
    void setWidth(int width) {this->width = width;}
    void setHeight(int height) {this->height = height;}
};

#endif // GRIDMODEL_H
