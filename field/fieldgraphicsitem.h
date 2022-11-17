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
    QPointF updatedPos() {
        return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
    }

protected:
    QPoint center;
    QSizeF cell_size;

signals:

public slots:
    void setCenter(const QPoint &center);
    void setCellSize(const QSizeF &cell_size);
};

#endif // FIELDGRAPHICSITEM_H
