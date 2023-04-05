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
    this->model = new CircuitElementModel();
    this->model->setCellsRect(QRect(-2, -2, 4, 4));
    this->graphics_item = this->model->getGraphicsItem();
    this->graphics_item->setImage(QImage(":/circuit_icons/resources/current.png"));
}

void CircuitBasicElementFactory::createE()
{
    this->model = new CircuitElementModel();
    this->model->setCellsRect(QRect(-2, -2, 4, 4));
    this->graphics_item = this->model->getGraphicsItem();
    this->graphics_item->setImage(QImage(":/circuit_icons/resources/voltage.png"));
}

void CircuitBasicElementFactory::createR()
{
    this->model = new CircuitElementModel();
    this->model->setCellsRect(QRect(-2, -2, 4, 4));
    this->graphics_item = this->model->getGraphicsItem();
    this->graphics_item->setImage(QImage(":/circuit_icons/resources/resistor.png"));
}

void CircuitBasicElementFactory::createC()
{
    this->model = new CircuitElementModel();
    this->model->setCellsRect(QRect(-2, -2, 4, 4));
    this->graphics_item = this->model->getGraphicsItem();
    this->graphics_item->setImage(QImage(":/circuit_icons/resources/capacitor.png"));
}

void CircuitBasicElementFactory::createL()
{
    this->model = new CircuitElementModel();
    this->model->setCellsRect(QRect(-2, -2, 4, 4));
    this->graphics_item = this->model->getGraphicsItem();
    this->graphics_item->setImage(QImage(":/circuit_icons/resources/inductor.png"));
}

void CircuitBasicElementFactory::createGnd()
{
    this->model = new CircuitElementModel();
    this->model->setCellsRect(QRect(-2, -2, 4, 4));
    this->graphics_item = this->model->getGraphicsItem();
    this->graphics_item->setImage(QImage(":/circuit_icons/resources/ground.png"));
}
