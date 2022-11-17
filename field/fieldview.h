#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

#include "grid/gridmodel.h"
#include "fieldgraphicsitem.h"


class FieldView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit FieldView(QWidget *parent = nullptr);
    ~FieldView();

    void setGridGraphicsItem(GridGraphicsItem *grid_graphics_item);
    void addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);
    void removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);

private:
    QGraphicsScene *scene;
    GridGraphicsItem *grid_graphics_item;

public slots:

};

#endif // FIELDVIEW_H
