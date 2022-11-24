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

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
        emit hoverEntered(this);

        Q_UNUSED(event);
    }

    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
        emit hoverLeaved(this);

        Q_UNUSED(event);
    }

signals:
    void hoverEntered(FieldGraphicsItem*);
    void hoverLeaved(FieldGraphicsItem*);

public slots:
    virtual void setCellSize(const QSizeF &cell_size);


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
