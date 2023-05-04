#ifndef WIREMODEL_H
#define WIREMODEL_H

#include <QObject>
#include <QPainterPath>
#include <QRect>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>

#include "../fieldelementmodel.h"
#include "../../libs/qpoint_hash.h"
#include "../../libs/objectcounter.h"

class WireModel;


class WireGraphicsItem : public FieldGraphicsItem
{
    Q_OBJECT

public:
    explicit WireGraphicsItem(QObject *parent = nullptr);
    WireGraphicsItem(const WireGraphicsItem &obj);
    ~WireGraphicsItem();
    FieldGraphicsItemType getType() {return FieldGraphicsItemType::WIRE;}

    QRectF boundingRect() const;
    QPainterPath shape() const;

    int getLineIndexByCoordinate(QPointF in_item_pos) const;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor line_color;
    QColor line_hover_color;
    QColor disable_color;
    qreal line_width;
    QPoint center;

    QPointF cursor_pos_cache;

    void init();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF updatedPos();
    QList<QLineF> getTransformedLines() const;
    QHash<QPointF, int> getTransformedLinesEndings() const;
    QPainterPath calcPathForLine(QLineF line_f) const;


public slots:
    virtual void attachFieldElementModel();
    virtual void detachFieldElementModel();
    void setCellSize(const QSizeF &cell_size);
    void setCenter(const QPoint &center);
    void setLineHoverColor(const QColor &line_hover_color);
    void setLineColor(const QColor &line_color);
    void setLineWidth(qreal width);
    void setVisibility(bool visible);
};


class WireModel : public FieldElementModel
{
    Q_OBJECT
public:
    explicit WireModel(QObject *parent = nullptr);
    WireModel(const WireModel &obj);
    ~WireModel();

    QRect getCellsRect() {return this->cells_rect;}
    QList<QLine> getLinesList() {return this->lines_list;}
    QHash<QPoint, int> getLinesEndings() {return this->lines_endings;}

    QList<WireModel*> removeWireLine(int line_index); // возвращает новые группы после удаления линии

    // wire algorithms
    static QList<QList<QLine>> regroupWire(const QList<QLine> &lines);
    static QList<QLine> recalculateWireStructure(const QList<QLine> &lines, QHash<QPoint, int> *line_endings);
    static QHash<QPoint, int> countLineEndings(const QList<QLine>& lines);
    static bool mergeOverlappingLines(const QHash<QPoint, int> &line_endings, const QLine &line1, const QLine &line2, QLine *line_result, bool axis);
    static bool mergePerpendicularTouching(const QLine &line1, const QLine &line2, QList<QLine> *line1_replacement, QList<QLine> *line2_replacement);

private:
    QRect cells_rect;
    QList<QLine> lines_list;
    QHash<QPoint, int> lines_endings;

    void updateCellsRect();

signals:
    void wireChanged();

public slots:
    void setCellsRect(const QRect &cells_rect) {this->cells_rect = cells_rect;}
    void setLinesList(const QList<QLine> &lines_list) {
        this->lines_list = this->recalculateWireStructure(lines_list, &lines_endings);
        this->updateCellsRect();
        emit wireChanged();
    }
};

#endif // WIREMODEL_H
