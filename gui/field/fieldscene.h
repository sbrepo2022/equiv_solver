#ifndef FIELDSCENE_H
#define FIELDSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QHash>
#include <QGraphicsSceneMouseEvent>

#include "field/fieldelementmodel.h"

class FieldScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit FieldScene(QObject *parent = nullptr);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QPointF last_pos;

    void sendHoverEvent(QEvent::Type type, QGraphicsItem *item, QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // FIELDSCENE_H
