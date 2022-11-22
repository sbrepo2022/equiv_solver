#ifndef WIREMODEL_H
#define WIREMODEL_H

#include <QObject>
#include <QRect>
#include <QPainter>

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

    QLineF getLineWithWireDirection(QPoint start_point, WireDirection wire_direction);

public slots:
    void setCellSize(const QSizeF &cell_size);
    void setCenter(const QPoint &center);
    void setLineColor(const QColor &line_color);
    void setLineWidth(qreal width);
    void setVisibility(bool visible);
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
    WireDirection getFirstDirection() {return this->first_direction;}
    WireDirection getSecondDirection() {return this->second_direction;}

private:
    static int object_count;
    int id;

    WireGraphicsItem *graphics_item;

    QRect cells_rect;
    QPoint center;
    WireDirection first_direction;
    WireDirection second_direction;

signals:
    void centerChanged(QPoint);

public slots:
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
    void setCenter(const QPoint &center) {
        this->center = center;
        emit centerChanged(this->center);
    }
    void setFirstDirection(WireDirection first_direction) {this->first_direction = first_direction;}
    void setSecondDirection(WireDirection second_direction) {this->second_direction = second_direction;}

};

#endif // WIREMODEL_H
