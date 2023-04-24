#include "fieldmodel.h"

int FieldModel::object_count = 0;

FieldModel::FieldModel(QObject *parent) : QObject(parent)
{
    id = FieldModel::object_count++;

    this->scene = new QGraphicsScene();
    this->grid_model = new GridModel();
    GridGraphicsItem *grid_graphics_item = this->grid_model->getGraphicsItem();
    this->connectWithGraphicsItem(grid_graphics_item);
    connect(this, &FieldModel::cellSizeChanged, this, &FieldModel::updateScene);

    connect(grid_graphics_item, &GridGraphicsItem::onCellEnter, this, &FieldModel::onCellEnter);
    connect(grid_graphics_item, &GridGraphicsItem::onCellLeave, this, &FieldModel::onCellLeave);
    connect(grid_graphics_item, &GridGraphicsItem::onItemEnter, this, &FieldModel::onGridEnter);
    connect(grid_graphics_item, &GridGraphicsItem::onItemLeave, this, &FieldModel::onGridLeave);
    connect(grid_graphics_item, &GridGraphicsItem::onCellPressed, this, &FieldModel::onCellPressed);

    grid_graphics_item->setZValue(0);
    this->scene->addItem(grid_graphics_item);
    this->scene->setSceneRect(grid_graphics_item->boundingRect());

    // debug
    this->graphics_item_debug = false;
}

FieldModel::~FieldModel()
{
    this->scene->removeItem(this->grid_model->getGraphicsItem());

    delete this->scene;
    delete this->grid_model;
}

void FieldModel::updateScene() {
    this->scene->setSceneRect(this->grid_model->getGraphicsItem()->boundingRect());
    this->scene->update();
}

void FieldModel::addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item, qreal z_index)
{
    if (field_graphics_item == nullptr) return;

    field_graphics_item->setCellSize(this->cell_size);

    // -- debug --
    field_graphics_item->setDebug(this->graphics_item_debug);
    // -- debug --

    this->connectWithGraphicsItem(field_graphics_item);

    if (this->scene != nullptr) {
        field_graphics_item->setZValue(z_index);
        this->scene->addItem(field_graphics_item);
    }
}

void FieldModel::removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item)
{
    if (field_graphics_item == nullptr) return;

    this->disconnectFromGraphicsItem(field_graphics_item);

    if (this->scene != nullptr) {
        this->scene->removeItem(field_graphics_item);
    }
}

void FieldModel::addCircuitElement(CircuitElementModel *circuit_element)
{
    CircuitElementGraphicsItem *graphics_item = circuit_element->getGraphicsItem();
    graphics_item->setColor(QColor(20, 0, 200));
    this->circuit_elements.insert(circuit_element->getId(), circuit_element);
    this->addFieldGraphicsItem(graphics_item, 75);
}

CircuitElementModel* FieldModel::removeCircuitElement(int id)
{
    if (! this->circuit_elements.contains(id)) return nullptr;

    CircuitElementModel *circuit_element = this->circuit_elements[id];
    CircuitElementGraphicsItem *graphics_item = circuit_element->getGraphicsItem();
    this->circuit_elements.remove(id);
    this->removeFieldGraphicsItem(graphics_item);
    return circuit_element;
}

void FieldModel::deleteCircuitElement(CircuitElementModel *circuit_element)
{
    if (circuit_element == nullptr) return;

    this->removeCircuitElement(circuit_element->getId());
    delete circuit_element;
}

void FieldModel::addWireElement(WireModel *wire)
{
    WireGraphicsItem *graphics_item = wire->getGraphicsItem();
    graphics_item->setLineColor(QColor(0, 200, 20));
    this->wires.insert(wire->getId(), wire);
    this->addFieldGraphicsItem(graphics_item, 50);
}

void FieldModel::addWireElementWithMerge(WireModel *wire)
{
    if (wire == nullptr) return;

    for (int i = 0; i < wires.count(); i++) {
        // дописать!!!
    }
}

WireModel* FieldModel::removeWireElement(int id)
{
    if (! this->wires.contains(id)) return nullptr;

    WireModel *wire = this->wires[id];
    WireGraphicsItem *graphics_item = wire->getGraphicsItem();
    this->wires.remove(id);
    this->removeFieldGraphicsItem(graphics_item);
    return wire;
}

void FieldModel::deleteWireLine(WireModel *wire, int line_index)
{
    if (wire == nullptr) return;

    QList<WireModel*> new_wire_models = wire->removeWireLine(line_index);
    for (WireModel *new_wire : new_wire_models) {
        this->addWireElement(new_wire);
    }

    this->removeWireElement(wire->getId());
    delete wire;
}

void FieldModel::connectWithGraphicsItem(FieldGraphicsItem *field_graphics_item)
{
    connect(this, &FieldModel::cellSizeChanged, field_graphics_item, &FieldGraphicsItem::setCellSize);
    connect(field_graphics_item, &FieldGraphicsItem::hoverEntered, this, &FieldModel::onGraphicsItemEntered);
    connect(field_graphics_item, &FieldGraphicsItem::hoverLeaved, this, &FieldModel::onGraphicsItemLeaved);
    connect(field_graphics_item, &FieldGraphicsItem::hoverMoved, this, &FieldModel::onGraphicsItemHoverMoved);
    connect(field_graphics_item, &FieldGraphicsItem::mousePressed, this, &FieldModel::onGraphicsItemMousePressed);

    // debug
    connect(this, &FieldModel::graphicsItemDebugChanged, field_graphics_item, &FieldGraphicsItem::setDebug);
}

void FieldModel::disconnectFromGraphicsItem(FieldGraphicsItem *field_graphics_item)
{
    disconnect(this, &FieldModel::cellSizeChanged, field_graphics_item, &FieldGraphicsItem::setCellSize);
    disconnect(field_graphics_item, &FieldGraphicsItem::hoverEntered, this, &FieldModel::onGraphicsItemEntered);
    disconnect(field_graphics_item, &FieldGraphicsItem::hoverLeaved, this, &FieldModel::onGraphicsItemLeaved);
    disconnect(field_graphics_item, &FieldGraphicsItem::hoverMoved, this, &FieldModel::onGraphicsItemHoverMoved);
    disconnect(field_graphics_item, &FieldGraphicsItem::mousePressed, this, &FieldModel::onGraphicsItemMousePressed);

    // debug
    disconnect(this, &FieldModel::graphicsItemDebugChanged, field_graphics_item, &FieldGraphicsItem::setDebug);
}

void FieldModel::setAcceptHoverEventsFromFieldElements(bool accept)
{
    this->setAcceptHoverEventsFromCircuitElements(accept);
    this->setAcceptHoverEventsFromWires(accept);
}

void FieldModel::setAcceptHoverEventsFromCircuitElements(bool accept)
{
    for (auto item : this->circuit_elements) {
        item->getGraphicsItem()->setAcceptHoverEvents(accept);
    }
}

void FieldModel::setAcceptHoverEventsFromWires(bool accept)
{
    for (auto item : this->wires) {
        item->getGraphicsItem()->setAcceptHoverEvents(accept);
    }
}
