#ifndef WIREMODEL_H
#define WIREMODEL_H

#include <QObject>
#include <QPainterPath>
#include <QRect>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>

#include "../fieldgraphicsitem.h"

class WireModel;


class WireGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit WireGraphicsItem(WireModel *model, QObject *parent = nullptr);
    ~WireGraphicsItem();
    WireModel* getModel() {return this->model;}
    FieldGraphicsItemType getType() {return FieldGraphicsItemType::WIRE;}

    WireGraphicsItem* clone(WireModel *model);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    int getLineIndexByCoordinate(QPointF in_item_pos) const;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    WireModel *model;
    QColor line_color;
    QColor line_hover_color;
    qreal line_width;
    QPoint center;

    qreal line_hover_distance_factor;
    QPointF cursor_pos_cache;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF updatedPos();
    QList<QLineF> getTransformedLines() const;
    QPainterPath calcPathForLine(QLineF line_f) const;


public slots:
    void setCellSize(const QSizeF &cell_size);
    void setCenter(const QPoint &center);
    void setLineHoverColor(const QColor &line_hover_color);
    void setLineColor(const QColor &line_color);
    void setLineWidth(qreal width);
    void setLineHoverDistanceFactor(qreal line_hover_distance_factor);
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
    QList<QLine> getLinesList() {return this->lines_list;}
    QPoint convertPointToLocal(const QPoint &point) {return point - this->center;}

    QList<WireModel*> removeWireLine(int line_index); // возвращает новые группы после удаления линии

    // wire algorithms
    static QList<QList<QLine>> regroupWire(const QList<QLine> &lines);
    static QList<QLine> recalculateWireStructure(const QList<QLine> &lines, QHash<QPoint, int> *line_endings);
    static QHash<QPoint, int> countLineEndings(const QList<QLine>& lines);
    static bool mergeOverlappingLines(const QHash<QPoint, int> &line_endings, const QLine &line1, const QLine &line2, QLine *line_result, bool axis);
    static bool mergePerpendicularTouching(const QLine &line1, const QLine &line2, QList<QLine> *line1_replacement, QList<QLine> *line2_replacement);

private:
    static int object_count;
    int id;

    WireGraphicsItem *graphics_item;

    QRect cells_rect;
    QPoint center;
    QList<QLine> lines_list;
    QHash<QPoint, int> lines_endings;

    void updateCellsRect();

signals:
    void centerChanged(QPoint);
    void wireChanged();

public slots:
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
    void setCenter(const QPoint &center) {
        this->center = center;
        emit centerChanged(this->center);
    }
    void setLinesList(const QList<QLine> &lines_list) {
        this->lines_list = this->recalculateWireStructure(lines_list, &lines_endings);
        this->updateCellsRect();
        emit wireChanged();
    }
};

#endif // WIREMODEL_H
