#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QHash>

#include "grid/gridmodel.h"
#include "fieldgraphicsitem.h"


class FieldView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit FieldView(QWidget *parent = nullptr);
    ~FieldView();

    //void addFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);
    //void removeFieldGraphicsItem(FieldGraphicsItem *field_graphics_item);

protected:

private:

public slots:
};

#endif // FIELDVIEW_H
