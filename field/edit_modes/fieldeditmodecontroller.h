#ifndef FIELDEDITMODECONTROLLER_H
#define FIELDEDITMODECONTROLLER_H

#include <QObject>

#include "../fieldmodel.h"

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
};

#endif // FIELDEDITMODECONTROLLER_H
