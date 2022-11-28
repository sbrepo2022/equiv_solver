#include "fieldscene.h"

FieldScene::FieldScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void FieldScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> curr_hovered_items = items(mouseEvent->scenePos());
    QList<QGraphicsItem*> prev_hovered_items = items(this->last_pos);
    QHash<QGraphicsItem*, bool> new_hovered_items;
    QHash<QGraphicsItem*, bool> cached_hovered_items;

    for (auto item : prev_hovered_items) {
        cached_hovered_items.insert(item, false);
    }

    for (auto item : curr_hovered_items) {
        if (! cached_hovered_items.contains(item)) {
            this->sendHoverEvent(QEvent::GraphicsSceneHoverEnter, item, mouseEvent);
        }
        else {
            cached_hovered_items[item] = true;
        }
        this->sendHoverEvent(QEvent::GraphicsSceneHoverMove, item, mouseEvent);
    }

    for (auto item = cached_hovered_items.begin(); item != cached_hovered_items.end(); item++) {
        if (! item.value()) {
            this->sendHoverEvent(QEvent::GraphicsSceneHoverLeave, item.key(), mouseEvent);
        }
    }

    this->last_pos = mouseEvent->scenePos();
}

void FieldScene::sendHoverEvent(QEvent::Type type, QGraphicsItem *item, QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsSceneHoverEvent hover(type);
    hover.setWidget(mouseEvent->widget());
    hover.setPos(item->mapFromScene(mouseEvent->scenePos()));
    hover.setScenePos(mouseEvent->scenePos());
    hover.setScreenPos(mouseEvent->screenPos());
    hover.setLastPos(item->mapFromScene(mouseEvent->lastScenePos()));
    hover.setLastScenePos(mouseEvent->lastScenePos());
    hover.setLastScreenPos(mouseEvent->lastScreenPos());
    hover.setModifiers(mouseEvent->modifiers());
    hover.setAccepted(mouseEvent->isAccepted());
    sendEvent(item, &hover);
}
