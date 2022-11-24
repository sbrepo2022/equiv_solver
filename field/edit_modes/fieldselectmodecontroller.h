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

signals:

public slots:
};

#endif // FIELDSELECTMODECONTROLLER_H
