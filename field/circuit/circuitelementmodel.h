#ifndef CIRCUITELEMENTMODEL_H
#define CIRCUITELEMENTMODEL_H

#include <QObject>
#include <QRect>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QRgb>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>

#include "../fieldgraphicsitem.h"

class CircuitElementModel;

class CircuitElementGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit CircuitElementGraphicsItem(CircuitElementModel *model, QObject *parent = nullptr);
    ~CircuitElementGraphicsItem();
    CircuitElementModel* getModel() {return this->model;}
    FieldGraphicsItemType getType() {return FieldGraphicsItemType::CIRCUIT_ELEMENT;}

    CircuitElementGraphicsItem* clone(CircuitElementModel *model);

    QRectF boundingRect() const;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    CircuitElementModel *model;
    QImage image;
    QImage draw_px;
    QColor color;
    QColor hover_color;
    QPoint center;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateDrawImage();
    QPointF updatedPos();

public slots:
    void setCellSize(const QSizeF &cell_size);
    void paramsUpdated();
    void setCenter(const QPoint &center);
    void setImage(const QImage &image);
    void setColor(const QColor &color);
    void setHoverColor(const QColor &hovered_color);
    void setVisibility(bool visible);
};


class CircuitElementModel : public QObject
{
    Q_OBJECT

public:
    explicit CircuitElementModel(QObject *parent = nullptr);
    CircuitElementModel(const CircuitElementModel &obj);
    ~CircuitElementModel();

    int getId() {return this->id;}

    CircuitElementGraphicsItem* getGraphicsItem() {return this->graphics_item;}

    int getAngle() {return this->angle;}
    QRect getCellsRect() {return this->cells_rect;}
    QPoint getCenter() {return this->center;}

private:
    static int object_count;
    int id;

    CircuitElementGraphicsItem* graphics_item;

    int angle; // 0, 1, 2 or 3
    QRect cells_rect;
    QPoint center;

signals:
    void centerChanged(QPoint);

public slots:
    void setAngle(int angle) {this->angle = angle;}
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
    void setCenter(const QPoint &center) {
        this->center = center;
        emit centerChanged(this->center);
    }
};

#endif // CIRCUITELEMENTMODEL_H
