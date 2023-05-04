#ifndef FIELDFACTORY_H
#define FIELDFACTORY_H

#include <QObject>

#include "fieldmodel.h"

class FieldFactory : public QObject
{
    Q_OBJECT
public:
    explicit FieldFactory(QObject *parent = nullptr);

    static FieldModel* createNew();

signals:

};

#endif // FIELDFACTORY_H
