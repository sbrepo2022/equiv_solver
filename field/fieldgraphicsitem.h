#ifndef FIELDGRAPHICSITEM_H
#define FIELDGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QMouseEvent>

enum class FieldGraphicsItemType
{
    GRID,
    CIRCUIT_ELEMENT,
    WIRE
};

class FieldGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit FieldGraphicsItem(QObject *parent = nullptr);
    virtual FieldGraphicsItemType getType() = 0;

private:

protected:
    QSizeF cell_size;

    bool mark_hovered;

signals:
    void hoverEntered(FieldGraphicsItem*);
    void hoverLeaved(FieldGraphicsItem*);
    void mousePressed(FieldGraphicsItem*, QGraphicsSceneMouseEvent*);

public slots:
    virtual void setCellSize(const QSizeF &cell_size);
    virtual void paramsUpdated() {this->update();}
    void setMarkHovered(bool mark_hovered) {this->mark_hovered = mark_hovered; this->paramsUpdated();}


// -- DEBUG --
protected:
    bool debug;

public slots:
    void setDebug(bool debug) {
        this->debug = debug;
        this->update();
    }
};

#endif // FIELDGRAPHICSITEM_H
