#include "circuitelementfactory.h"

CircuitBasicElementFactory::CircuitBasicElementFactory(BasicElementType el_type)
{
    switch (el_type) {
        case BasicElementType::I:
            createI();
            break;

        case BasicElementType::E:
            createE();
            break;

        case BasicElementType::R:
            createR();
            break;

        case BasicElementType::C:
            createC();
            break;

        case BasicElementType::L:
            createL();
            break;

    case BasicElementType::Gnd:
        createGnd();
        break;
    }
}


void CircuitBasicElementFactory::createI()
{
    this->model = new CurrencySourceElementModel();
    this->graphics_item = this->model->getGraphicsItem<CircuitElementGraphicsItem>();
}

void CircuitBasicElementFactory::createE()
{
    this->model = new VoltageSourceElementModel();
    this->graphics_item = this->model->getGraphicsItem<CircuitElementGraphicsItem>();
}

void CircuitBasicElementFactory::createR()
{
    this->model = new ResistorElementModel();
    this->graphics_item = this->model->getGraphicsItem<CircuitElementGraphicsItem>();
}

void CircuitBasicElementFactory::createC()
{
    this->model = new CapacitorElementModel();
    this->graphics_item = this->model->getGraphicsItem<CircuitElementGraphicsItem>();
}

void CircuitBasicElementFactory::createL()
{
    this->model = new InductorElementModel();
    this->graphics_item = this->model->getGraphicsItem<CircuitElementGraphicsItem>();
}

void CircuitBasicElementFactory::createGnd()
{
    this->model = new GroundElementModel();
    this->graphics_item = this->model->getGraphicsItem<CircuitElementGraphicsItem>();
}
