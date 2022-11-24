#ifndef WIREMODEL_H
#define WIREMODEL_H

#include <QObject>
#include <QRect>
#include <QPainter>
#include <QDebug>

#include "../fieldgraphicsitem.h"

enum WireDirectionType {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};


class WireDirection
{
public:
    WireDirection() : type(WireDirectionType::TOP), length(0) {}
    WireDirection(WireDirectionType type, int length) : type(type), length(length) {}

    WireDirectionType getType() {return this->type;}
    int getLength() {return this->length;}

    void setType(WireDirectionType type) {this->type = type;}
    void setLength(int length) {this->length = length;}

private:
    WireDirectionType type;
    int length;
};


class WireModel;


class WireGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit WireGraphicsItem(WireModel *model, QObject *parent = nullptr);
    ~WireGraphicsItem();

    WireGraphicsItem* clone(WireModel *model);

    QRectF boundingRect() const;

private:
    WireModel *model;
    QColor line_color;
    qreal line_width;
    QPoint center;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF updatedPos();


public slots:
    void setCellSize(const QSizeF &cell_size);
    void setCenter(const QPoint &center);
    void setLineColor(const QColor &line_color);
    void setLineWidth(qreal width);
    void setVisibility(bool visible);
    void paramsUpdated();
};


class WireModel : public QObject
{
    Q_OBJECT
public:
    explicit WireModel(QObject *parent = nullptr);
    WireModel(const WireModel &obj);
    ~WireModel();

    int getId() {return this->id;}

    WireGraphicsItem* getGraphicsItem() {return this->graphics_item;}

    QRect getCellsRect() {return this->cells_rect;}
    QPoint getCenter() {return this->center;}
    QPolygon getPoints() {return this->points;}
    QPoint convertPointToLocal(const QPoint &point) {return point - this->center;}

private:
    static int object_count;
    int id;

    WireGraphicsItem *graphics_item;

    QRect cells_rect;
    QPoint center;
    QPolygon points;

    void updateCellsRect();

signals:
    void centerChanged(QPoint);
    void pointsChanged();

public slots:
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
    void setCenter(const QPoint &center) {
        this->center = center;
        emit centerChanged(this->center);
    }
    void setPoints(const QPolygon &points) {
        this->points = points;
        this->updateCellsRect();
        emit pointsChanged();
    }

};

#endif // WIREMODEL_H
