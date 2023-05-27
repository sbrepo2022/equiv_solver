#ifndef CIRCUITELEMENTFACTORY_H
#define CIRCUITELEMENTFACTORY_H

#include "field/circuit/circuitelementmodel.h"
#include "field/circuit/standart_circuit_elements/currencysourceelementmodel.h"
#include "field/circuit/standart_circuit_elements/voltagesourceelementmodel.h"
#include "field/circuit/standart_circuit_elements/resistorelementmodel.h"
#include "field/circuit/standart_circuit_elements/capacitorelementmodel.h"
#include "field/circuit/standart_circuit_elements/inductorelementmodel.h"
#include "field/circuit/standart_circuit_elements/groundelementmodel.h"

enum BasicElementType {
    I,
    E,
    R,
    C,
    L,
    Gnd
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
    void createGnd();
};

#endif // CIRCUITELEMENTFACTORY_H
