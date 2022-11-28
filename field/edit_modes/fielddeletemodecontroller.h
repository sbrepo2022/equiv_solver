#ifndef FIELDDELETEMODECONTROLLER_H
#define FIELDDELETEMODECONTROLLER_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "fieldselectmodecontroller.h"

class FieldDeleteModeController : public FieldSelectModeController
{
    Q_OBJECT
public:
    explicit FieldDeleteModeController(QObject *parent = nullptr);

    void detachFieldModel();
    void attachFieldModel(FieldModel *field_model);

signals:

public slots:
    void onGraphicsItemMousePressed(FieldGraphicsItem *graphics_item, QGraphicsSceneMouseEvent *event);
};

#endif // FIELDDELETEMODECONTROLLER_H
