#ifndef FIELDDRAWELEMENTMODECONTROLLER_H
#define FIELDDRAWELEMENTMODECONTROLLER_H

#include <QObject>

#include "fieldeditmodecontroller.h"
#include "../circuit/circuitelementmodel.h"

class FieldDrawElementModeController : public FieldEditModeController
{
    Q_OBJECT
public:
    explicit FieldDrawElementModeController(QObject *parent = nullptr);

    void detachFieldModel();
    void attachFieldModel(FieldModel *field_model);

    void setCircuitElement(CircuitElementModel *circuit_model);

private:
    CircuitElementModel *buffer_element;
    CircuitElementGraphicsItem *buffer_graphics_item;
    bool buffer_element_collided;

signals:

public slots:
    virtual void actionTriggered(QString action_name);

    void gridCellHover(const QPoint &pos);
    void gridItemEnter();
    void gridItemLeave();
    void gridCellPressed(const QPoint &pos);
};

#endif // FIELDDRAWELEMENTMODECONTROLLER_H
