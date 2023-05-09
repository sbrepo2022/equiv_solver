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

#include "../fieldelementmodel.h"
#include "../../model_components/selectablemodelcomponentskeeper.h"
#include "../../libs/qpoint_hash.h"

class InputPointData {
private:
    QPoint point;
    QPointF normalized_vector;
    QString name;

    int angle_value; // 0, 1, 2, 3

    QTransform getAngleTransform() {
        QTransform transform;
        transform = transform.rotate(90 * this->angle_value);
        return transform;
    }

    static QPointF normalizeVector(QPointF vector) {
        return vector;
    }

public:
    InputPointData(QPoint point, QPoint vector, QString name) : point(point), normalized_vector(QPointF()), name(name), angle_value(0) {
        this->normalized_vector = InputPointData::normalizeVector(vector);
    }

    InputPointData withAngle(int angle_value) const {
        InputPointData obj_copy = InputPointData(*this);
        obj_copy.angle_value = angle_value;
        return obj_copy;
    }

    QPoint getPoint() {
        QTransform transform = this->getAngleTransform();
        return transform.map(this->point);
    }

    QPointF getPointF(QSizeF cell_size) {
        QTransform transform = this->getAngleTransform();
        transform = transform.scale(cell_size.width(), cell_size.height());
        return transform.map(this->point);
    }

    QPointF getNormalizedVector() {
        QTransform transform = this->getAngleTransform();
        return transform.map(this->normalized_vector);
    }

    QString getName() {
        return this->name;
    }

    QRectF calculateInputRect(QSizeF cell_size, qreal w_factor, qreal h_factor) {
        QPointF point_f = this->getPointF(cell_size);
        QPointF vector_f = this->getNormalizedVector();
        QPointF normal_f = QPointF(vector_f.y(), vector_f.x());

        QVector<QPointF> rect_points = {
            point_f + normal_f * w_factor / 2,
            point_f - normal_f * w_factor / 2,
            point_f - normal_f * w_factor / 2 + vector_f * h_factor,
            point_f + normal_f * w_factor / 2 + vector_f * h_factor
        };

        QRectF rect(rect_points[0], rect_points[1]);
        rect = rect.united(QRectF(rect_points[2], rect_points[3]));
        rect = rect.normalized();

        return rect;
    }
};

class CircuitElementModel;

class CircuitElementGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit CircuitElementGraphicsItem(QObject *parent = nullptr);
    CircuitElementGraphicsItem(const CircuitElementGraphicsItem &obj);
    ~CircuitElementGraphicsItem();
    FieldGraphicsItemType getType() {return FieldGraphicsItemType::CIRCUIT_ELEMENT;}

    QRectF getBasicRect() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QImage image;
    QImage draw_px;
    QColor color;
    QColor hover_color;
    QColor selection_color;
    QColor disable_color;
    QPoint center;

    void init();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateDrawImage();
    QPointF updatedPos();

public slots:
    virtual void attachFieldElementModel();
    virtual void detachFieldElementModel();
    void setCellSize(const QSizeF &cell_size);
    void paramsUpdated();
    void setCenter(const QPoint &center);
    void setImage(const QImage &image);
    void setColor(const QColor &color);
    void setHoverColor(const QColor &hovered_color);
    void setSelectionColor(const QColor &selection_color);
    void setDisableColor(const QColor &disable_color);
    void setVisibility(bool visible);
};


class CircuitElementModel : public FieldElementModel, public SelectableModelComponentsKeeper
{
    Q_OBJECT

public:
    CircuitElementModel(QObject *parent = nullptr);
    CircuitElementModel(const CircuitElementModel &obj);
    ~CircuitElementModel();

    int getAngle() {return this->angle;}
    QRect getCellsRect() {return this->cells_rect;}
    QHash<QPoint, InputPointData> getInputsPoints() { return this->inputs_points; }
    QPoint getCenter() {return this->center;}

private:
    int angle; // 0, 1, 2 or 3
    QRect cells_rect;
    QHash<QPoint, InputPointData> inputs_points;
    QPoint center;

signals:
    void centerChanged(QPoint);

public slots:
    void setAngle(int angle) {this->angle = angle;}
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
    void setInputsPoints(const QHash<QPoint, InputPointData> &inputs_points) {this->inputs_points = inputs_points;}
    void setCenter(const QPoint &center) {
        this->center = center;
        emit centerChanged(this->center);
    }
    void rotateRight() {
        this->angle++;
        if (this->angle > 3) this->angle = 0;
        this->getGraphicsItem<CircuitElementGraphicsItem>()->paramsUpdated();
    }
    void rotateLeft() {
        this->angle--;
        if (this->angle < 0) this->angle = 3;
        this->getGraphicsItem<CircuitElementGraphicsItem>()->paramsUpdated();
    }
};

#endif // CIRCUITELEMENTMODEL_H
