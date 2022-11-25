#ifndef FIELDGRAPHICSITEM_H
#define FIELDGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

class FieldGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit FieldGraphicsItem(QObject *parent = nullptr);

private:

protected:
    QSizeF cell_size;

    bool mark_hovered;

signals:
    void hoverEntered(FieldGraphicsItem*);
    void hoverLeaved(FieldGraphicsItem*);

public slots:
    virtual void setCellSize(const QSizeF &cell_size);
    void setMarkHovered(bool mark_hovered) {this->mark_hovered = mark_hovered; this->paramsUpdated();}
    void paramsUpdated() {this->update();}


// -- DEBUG --
protected:
    bool debug;

public slots:
    void setDebug(bool debug) {
        this->debug = debug;
        this->update();
    }
};

#endif // FIELDGRAPHICSITEM_H
