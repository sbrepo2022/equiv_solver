#include "fieldelementmodel.h"

FieldGraphicsItem::FieldGraphicsItem(QObject *parent) :
    QObject(parent),
    QGraphicsItem()
{
    this->init();
}

FieldGraphicsItem::FieldGraphicsItem(const FieldGraphicsItem &obj)
    : QObject(obj.parent()), QGraphicsItem()
{
    this->init();

    this->model = obj.model;

    this->cell_size = obj.cell_size;
    this->mark_hovered = obj.mark_hovered;
    this->mark_collided = obj.mark_collided;

    this->debug = obj.debug;
}

void FieldGraphicsItem::init()
{
    this->model = nullptr;

    this->cell_size = QSizeF(32, 32);
    this->mark_hovered = false;
    this->mark_selected = false;
    this->mark_collided = false;

    this->debug = false;

    this->setAcceptHoverEvents(false);
    //this->setAcceptedMouseButtons(Qt::LeftButton);

    bool loaded = this->forbidden_renderer.load(QStringLiteral(":/ui_icons/resources/ui_icons/forbidden.svg"));
    if (!loaded) {
        qDebug() << "Unable to loading 'forbidden.svg'!";
    }
}

void FieldGraphicsItem::setCellSize(const QSizeF &cell_size) {
    this->cell_size = cell_size;
}


template class ObjectCounter<FieldElementModel>;

FieldElementModel::FieldElementModel(QObject *parent) : QObject(parent), ObjectCounter<FieldElementModel>()
{
    this->graphics_item = nullptr;
}

FieldElementModel::~FieldElementModel()
{
    delete this->graphics_item;
}

FieldElementModel::FieldElementModel(const FieldElementModel &obj) : QObject(obj.parent())
{
    this->graphics_item = nullptr;
}
