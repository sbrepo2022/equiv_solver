#include "fieldfactory.h"

FieldFactory::FieldFactory(QObject *parent) : QObject(parent)
{

}

FieldModel* FieldFactory::createNew() {
    return new FieldModel();
}
