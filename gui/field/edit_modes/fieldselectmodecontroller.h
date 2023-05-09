#ifndef FIELDSELECTMODECONTROLLER_H
#define FIELDSELECTMODECONTROLLER_H

#include <QObject>

#include "fieldeditmodecontroller.h"
#include "../../model_components/selectablemodelcomponentskeeper.h"

class FieldSelectModeController : public FieldEditModeController
{
    Q_OBJECT
public:
    explicit FieldSelectModeController(QObject *parent = nullptr);

    void detachFieldModel();
    void attachFieldModel(FieldModel *field_model);
    void cancelObjectSelection();

private:
    FieldGraphicsItem *current_graphics_item;
    FieldGraphicsItem *selected_graphics_item;

protected:
    void clearCurrentGraphicsItem() {
        this->current_graphics_item = nullptr;
        this->selected_graphics_item = nullptr;
    }

signals:
    void selectableModelSelected(SelectableModelComponentsKeeper*);

public slots:
    void onGraphicsItemEntered(FieldGraphicsItem *graphics_item);
    void onGraphicsItemLeaved(FieldGraphicsItem *graphics_item);
    void onGraphicsItemHoverMoved(FieldGraphicsItem *graphics_item, QGraphicsSceneHoverEvent *event);
    void onGraphicsItemMousePressed(FieldGraphicsItem *graphics_item, QGraphicsSceneMouseEvent *event);
};

#endif // FIELDSELECTMODECONTROLLER_H
