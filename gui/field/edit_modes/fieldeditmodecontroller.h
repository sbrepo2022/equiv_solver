#ifndef FIELDEDITMODECONTROLLER_H
#define FIELDEDITMODECONTROLLER_H

#include <QObject>

#include "field/fieldmodel.h"

class FieldEditModeController : public QObject
{
    Q_OBJECT
public:
    explicit FieldEditModeController(QObject *parent = nullptr);

    virtual void detachFieldModel();
    virtual void attachFieldModel(FieldModel *field_model);

    FieldModel *getCurrentFieldModel() {return this->field_model;}

private:
    FieldModel *field_model;

signals:

public slots:
    virtual void actionTriggered(QString action_name);
};

#endif // FIELDEDITMODECONTROLLER_H
