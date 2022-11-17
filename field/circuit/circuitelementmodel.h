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
    QPixmap draw_px;
    QColor color;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateDrawImage();

public slots:
    void setImage(const QImage &image);
    void setColor(const QColor &color);
};


class CircuitElementModel : public QObject
{
    Q_OBJECT

public:
    explicit CircuitElementModel(QObject *parent = nullptr);
    CircuitElementGraphicsItem* createCircuitElementGraphicsItem();

    int getAngle() {return this->angle;}
    QRect getCellsRect() {return this->cells_rect;}

private:
    int angle; // 0, 1, 2 or 3
    QRect cells_rect;

signals:

public slots:
    void setAngle(int angle) {this->angle = angle;}
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
};

#endif // CIRCUITELEMENTMODEL_H
