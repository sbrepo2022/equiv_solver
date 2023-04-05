#ifndef FIELDSELECTMODECONTROLLER_H
#define FIELDSELECTMODECONTROLLER_H

#include <QObject>

#include "fieldeditmodecontroller.h"

class FieldSelectModeController : public FieldEditModeController
{
    Q_OBJECT
public:
    explicit FieldSelectModeController(QObject *parent = nullptr);

    void detachFieldModel();
    void attachFieldModel(FieldModel *field_model);

private:
    FieldGraphicsItem *current_graphics_item;

protected:
    void clearCurrentGraphicsItem() { this->current_graphics_item = nullptr; }

signals:

public slots:
    void onGraphicsItemEntered(FieldGraphicsItem *graphics_item);
    void onGraphicsItemLeaved(FieldGraphicsItem *graphics_item);
};

#endif // FIELDSELECTMODECONTROLLER_H
