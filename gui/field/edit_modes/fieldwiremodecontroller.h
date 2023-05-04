#ifndef FIELDWIREMODECONTROLLER_H
#define FIELDWIREMODECONTROLLER_H

#include <QObject>

#include "fieldeditmodecontroller.h"
#include "../wire/wiremodel.h"

class FieldWireModeController : public FieldEditModeController
{
    Q_OBJECT
public:
    explicit FieldWireModeController(QObject *parent = nullptr);

    void detachFieldModel();
    void attachFieldModel(FieldModel *field_model);

private:
    WireModel *buffer_wire;
    WireGraphicsItem *buffer_wire_graphics_item;
    bool wire_started;
    bool buffer_element_collided;

    void startWire(const QPoint &pos);
    void finishWire();
    void clearBufferWire();
    bool checkIsAllCollidedItemsIsWire(const QList<QGraphicsItem*> &colliding_items);

signals:

public slots:
    void gridCellHover(const QPoint &pos);
    void gridItemEnter();
    void gridItemLeave();
    void gridCellPressed(const QPoint &pos);
};

#endif // FIELDWIREMODECONTROLLER_H
