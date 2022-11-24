#ifndef FIELDDELETEMODECONTROLLER_H
#define FIELDDELETEMODECONTROLLER_H

#include <QObject>

#include "fieldeditmodecontroller.h"

class FieldDeleteModeController : public FieldEditModeController
{
    Q_OBJECT
public:
    explicit FieldDeleteModeController(QObject *parent = nullptr);

    void detachFieldModel();
    void attachFieldModel(FieldModel *field_model);

signals:

public slots:
};

#endif // FIELDDELETEMODECONTROLLER_H
