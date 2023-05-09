#include "fieldmodel.h"

int FieldModel::object_count = 0;

FieldModel::FieldModel(QObject *parent) : QObject(parent)
{
    id = FieldModel::object_count++;

    this->scene = new QGraphicsScene();
    this->grid_model = new GridModel();
    GridGraphicsItem *grid_graphics_item = this->grid_model->getGraphicsItem<GridGraphicsItem>();
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
    this->scene->removeItem(this->grid_model->getGraphicsItem<GridGraphicsItem>());

    delete this->scene;
    delete this->grid_model;
}

void FieldModel::updateScene() {
    this->scene->setSceneRect(this->grid_model->getGraphicsItem<GridGraphicsItem>()->boundingRect());
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
    if (circuit_element == nullptr) return;
    CircuitElementGraphicsItem *graphics_item = circuit_element->getGraphicsItem<CircuitElementGraphicsItem>();
    graphics_item->setColor(QColor(20, 0, 200));
    this->circuit_elements.insert(circuit_element->getId(), circuit_element);
    this->addFieldGraphicsItem(graphics_item, 75);

    FieldElementPropertiesComponent *field_element_properties_component = qobject_cast<FieldElementPropertiesComponent*>(circuit_element->getPropertiesComponent());
    if (field_element_properties_component != nullptr) {
        field_element_properties_component->installedToField();
    }
}

CircuitElementModel* FieldModel::removeCircuitElement(int id)
{
    if (! this->circuit_elements.contains(id)) return nullptr;

    CircuitElementModel *circuit_element = this->circuit_elements[id];
    CircuitElementGraphicsItem *graphics_item = circuit_element->getGraphicsItem<CircuitElementGraphicsItem>();
    this->circuit_elements.remove(id);
    this->removeFieldGraphicsItem(graphics_item);
    return circuit_element;
}

void FieldModel::deleteCircuitElement(CircuitElementModel *circuit_element)
{
    if (circuit_element == nullptr) return;

    this->removeCircuitElement(circuit_element->getId());
    circuit_element->deleteLater();
}

void FieldModel::addWireElement(WireModel *wire)
{
    WireGraphicsItem *graphics_item = wire->getGraphicsItem<WireGraphicsItem>();
    graphics_item->setLineColor(QColor(0, 200, 20));
    this->wires.insert(wire->getId(), wire);
    this->addFieldGraphicsItem(graphics_item, 50);
}

void FieldModel::addWireElementWithMerge(WireModel *wire)
{
    if (wire == nullptr) return;

    QList<int> merged_models_ids;
    for (int id : wires.keys()) {
        QList<QLine> merged_lines;
        merged_lines << wires[id]->getLinesList();
        merged_lines << wire->getLinesList();

        QHash<QPoint, int> line_endings_count;
        QList<QList<QLine>> lines_groups;
        merged_lines = WireModel::recalculateWireStructure(merged_lines, &line_endings_count);

        lines_groups = WireModel::regroupWire(merged_lines);

        if (lines_groups.count() == 1) {
            merged_models_ids << id;
        }
    }

    QList<QLine> lines_list;
    WireModel *removed_wire;
    lines_list << wire->getLinesList();
    for (int id : merged_models_ids) {
        lines_list << wires[id]->getLinesList();
        removed_wire = this->removeWireElement(id);
        delete removed_wire;
    }
    wire->setLinesList(lines_list);

    this->addWireElement(wire);
}

WireModel* FieldModel::removeWireElement(int id)
{
    if (! this->wires.contains(id)) return nullptr;

    WireModel *wire = this->wires[id];
    WireGraphicsItem *graphics_item = wire->getGraphicsItem<WireGraphicsItem>();
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
    wire->deleteLater();
}

bool FieldModel::checkItemCollision(QGraphicsItem *graphics_item, QGraphicsScene *scene, QList<QGraphicsItem*> *colliding_out_list)
{
    QList<QGraphicsItem*> colliding_items = scene->collidingItems(graphics_item);
    for (int i = 0; i < colliding_items.count(); i++) {
        GridGraphicsItem *grid_graphics_item = dynamic_cast<GridGraphicsItem*>(colliding_items[i]);
        if (grid_graphics_item != nullptr) {
            colliding_items.removeAt(i);
            i--;
        }
    }

    if (colliding_out_list != nullptr) *colliding_out_list = colliding_items;

    if (colliding_items.isEmpty()) {
        return false;
    }

    return true;
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
        item->getGraphicsItem<CircuitElementGraphicsItem>()->setAcceptHoverEvents(accept);
    }
}

void FieldModel::setAcceptHoverEventsFromWires(bool accept)
{
    for (auto item : this->wires) {
        item->getGraphicsItem<WireGraphicsItem>()->setAcceptHoverEvents(accept);
    }
}
