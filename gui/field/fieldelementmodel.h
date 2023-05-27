#ifndef FIELDELEMENTMODEL_H
#define FIELDELEMENTMODEL_H

#include <QObject>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QDebug>

#include "libs/objectcounter.h"


enum class FieldGraphicsItemType
{
    GRID,
    CIRCUIT_ELEMENT,
    WIRE
};

class FieldElementModel;

class FieldGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit FieldGraphicsItem(QObject *parent = nullptr);
    FieldGraphicsItem(const FieldGraphicsItem &obj);
    virtual FieldGraphicsItemType getType() = 0;

    FieldGraphicsItem *withModel(FieldElementModel *model) {
        if (this->model != nullptr) this->detachFieldElementModel();
        this->model = model;
        this->attachFieldElementModel();
        return this;
    }

    template<class ModelClass>
    ModelClass* getModel() const {
        return dynamic_cast<ModelClass*>(this->model);
    }

private:
    FieldElementModel *model;

    void init();

protected:
    QSizeF cell_size;

    bool mark_hovered;
    bool mark_selected;
    bool mark_collided;

    QSvgRenderer forbidden_renderer;

signals:
    void hoverEntered(FieldGraphicsItem*);
    void hoverLeaved(FieldGraphicsItem*);
    void hoverMoved(FieldGraphicsItem*, QGraphicsSceneHoverEvent*);
    void mousePressed(FieldGraphicsItem*, QGraphicsSceneMouseEvent*);

public slots:
    virtual void attachFieldElementModel() = 0;
    virtual void detachFieldElementModel() = 0;
    virtual void setCellSize(const QSizeF &cell_size);

    virtual void paramsUpdated() {
        this->update();
    }

    virtual void setCenter(const QPoint &center) {
        this->setPos(QPoint(center.x() * cell_size.width(), center.y() * cell_size.height()));
    }

    void setMarkHovered(bool mark_hovered) {
        this->mark_hovered = mark_hovered;
        this->paramsUpdated();
    }

    void setMarkSelected(bool mark_selected) {
        this->mark_selected = mark_selected;
        this->paramsUpdated();
    }

    void setMarkCollided(bool mark_collided) {
        this->mark_collided = mark_collided;
        this->paramsUpdated();
    }

// -- DEBUG --
protected:
    bool debug;

public slots:
    void setDebug(bool debug) {
        this->debug = debug;
        this->update();
    }
};

class FieldElementModel : public QObject, public ObjectCounter<FieldElementModel>
{
    Q_OBJECT
public:
    template<class GraphicsItemClass>
    static GraphicsItemClass* createGraphicsItem(FieldElementModel *model, QObject *parent = nullptr) {
        return qobject_cast<GraphicsItemClass*>((new GraphicsItemClass(parent))->withModel(model));
    }

    template<class GraphicsItemClass>
    GraphicsItemClass* cloneGraphicsItem(FieldElementModel *model) const {
        GraphicsItemClass *item_without_model = new GraphicsItemClass(*(this->getGraphicsItem<GraphicsItemClass>()));
        GraphicsItemClass *item_cloned = qobject_cast<GraphicsItemClass*>(item_without_model->withModel(model));
        return item_cloned;
    }

    explicit FieldElementModel(QObject *parent = nullptr);
    FieldElementModel(const FieldElementModel &obj);
    virtual ~FieldElementModel();

    virtual FieldElementModel* copy() {
        return (new FieldElementModel(*this));
    }

    template<class GraphicsItemClass>
    GraphicsItemClass* getGraphicsItem() const {
        return qobject_cast<GraphicsItemClass*>(this->graphics_item);
    }

    void setGraphicsItem(FieldGraphicsItem *graphics_item) { this->graphics_item = graphics_item; }

private:
    FieldGraphicsItem *graphics_item;

signals:

public slots:
};

#endif // FIELDELEMENTMODEL_H
