#ifndef CIRCUITELEMENTFACTORY_H
#define CIRCUITELEMENTFACTORY_H

#include "circuitelementmodel.h"

enum BasicElementType {
    I,
    E,
    R,
    C,
    L
};

class CircuitBasicElementFactory
{
public:
    CircuitBasicElementFactory(BasicElementType el_type);

    CircuitElementModel *model;
    CircuitElementGraphicsItem *graphics_item;

private:
    void createI();
    void createE();
    void createR();
    void createC();
    void createL();
};

#endif // CIRCUITELEMENTFACTORY_H
