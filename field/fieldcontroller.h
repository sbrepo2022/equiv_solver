#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include <QObject>
#include "fieldview.h"
#include "grid/gridmodel.h"
#include "circuit/circuitelementmodel.h"
#include "circuit/circuitelementfactory.h"

enum FieldEditMode {
    SELECT,
    WIRE,
    DELETE,
    DRAW_ELEMENT,
};

class FieldController : public QObject
{
    Q_OBJECT

public:
    explicit FieldController(FieldView *field_view, QObject *parent = nullptr);
    void setDrawElementsMode(CircuitElementModel *model, CircuitElementGraphicsItem *graphics_item);

private:
    FieldView *field_view;
    FieldEditMode edit_mode = FieldEditMode::SELECT;

    GridModel grid_model;
    QSizeF cell_size;

    CircuitElementModel *buffer_element;
    CircuitElementGraphicsItem *buffer_graphics_item;
    QList <CircuitElementModel*> circuit_elements;

signals:

public slots:

};

#endif // FIELDCONTROLLER_H
