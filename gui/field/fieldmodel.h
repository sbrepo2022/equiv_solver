#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QObject>
#include <QMap>
#include <QGraphicsScene>

#include "fieldscene.h"
#include "grid/gridmodel.h"
#include "circuit/circuitelementmodel.h"
#include "wire/wiremodel.h"

class FieldModel : public QObject
{
    Q_OBJECT
public:
    explicit FieldModel(QObject *parent = nullptr);
    ~FieldModel();

    int getId() {return this->id;}
    QGraphicsScene* getScene() {return this->scene;}

    QSize getGridSize() {return this->grid_model->getGridSize();}

    GridGraphicsItem* getGridGraphicsItem() {return this->grid_model->getGraphicsItem<GridGraphicsItem>();}

    void addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item, qreal z_index);
    void removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);

    void addCircuitElement(CircuitElementModel *circuit_element);
    CircuitElementModel* removeCircuitElement(int id);
    void deleteCircuitElement(CircuitElementModel *circuit_element);

    void addWireElement(WireModel *wire);
    void addWireElementWithMerge(WireModel *wire);
    WireModel* removeWireElement(int id);
    void deleteWireLine(WireModel *wire, int line_index);

    bool checkItemCollision(QGraphicsItem *graphics_item, QGraphicsScene *scene, QList<QGraphicsItem*> *colliding_out_list = nullptr);

private:
    static int object_count;

    int id;
    QSizeF cell_size;
    QGraphicsScene *scene;
    GridModel *grid_model;
    QMap <int, CircuitElementModel*> circuit_elements;
    QMap <int, WireModel*> wires;

    void connectWithGraphicsItem(FieldGraphicsItem *field_graphics_item);
    void disconnectFromGraphicsItem(FieldGraphicsItem *field_graphics_item);

signals:
    void cellSizeChanged(QSizeF);

    void onCellLeave(QPoint);
    void onCellEnter(QPoint);
    void onGridEnter();
    void onGridLeave();
    void onCellPressed(QPoint);

    void onGraphicsItemEntered(FieldGraphicsItem*);
    void onGraphicsItemLeaved(FieldGraphicsItem*);
    void onGraphicsItemHoverMoved(FieldGraphicsItem*, QGraphicsSceneHoverEvent*);
    void onGraphicsItemMousePressed(FieldGraphicsItem*, QGraphicsSceneMouseEvent*);

public slots:
    void setCellSize(const QSizeF &cell_size) {
        this->cell_size = cell_size;
        emit cellSizeChanged(cell_size);
    }
    void setGridSize(const QSize &grid_size) {this->grid_model->setGridSize(grid_size);}
    void setAcceptHoverEventsFromFieldElements(bool accept);
    void setAcceptHoverEventsFromCircuitElements(bool accept);
    void setAcceptHoverEventsFromWires(bool accept);
    void updateScene();

// -- DEBUG --
private:
    bool graphics_item_debug;

signals:
    void graphicsItemDebugChanged(bool);

public slots:
    void setGraphicsItemDebug(bool checked) {
        this->graphics_item_debug = checked;
        emit graphicsItemDebugChanged(checked);
    }
};

#endif // FIELDMODEL_H
