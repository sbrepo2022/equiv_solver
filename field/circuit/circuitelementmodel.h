#ifndef CIRCUITELEMENTMODEL_H
#define CIRCUITELEMENTMODEL_H

#include <QObject>
#include <QRect>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QRgb>
#include <QPainter>
#include <QDebug>

#include "../fieldgraphicsitem.h"

class CircuitElementModel;

class CircuitElementGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit CircuitElementGraphicsItem(CircuitElementModel *model, QObject *parent = nullptr);
    ~CircuitElementGraphicsItem();

    QRectF boundingRect() const;

private:
    CircuitElementModel *model;
    QImage image;
    QImage draw_px;
    QColor color;
    QPoint center;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateDrawImage();
    QPointF updatedPos();

public slots:
    void setCellSize(const QSizeF &cell_size);
    void setCenter(const QPoint &center);
    void setImage(const QImage &image);
    void setColor(const QColor &color);
    void setVisibility(bool visible);
};


class CircuitElementModel : public QObject
{
    Q_OBJECT

public:
    explicit CircuitElementModel(QObject *parent = nullptr);
    ~CircuitElementModel();
    CircuitElementGraphicsItem* createCircuitElementGraphicsItem();

    int getAngle() {return this->angle;}
    QRect getCellsRect() {return this->cells_rect;}

    CircuitElementModel* clone();

private:
    QList<CircuitElementGraphicsItem*> graphics_items;

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
