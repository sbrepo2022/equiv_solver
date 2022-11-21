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

signals:

public slots:
    virtual void setCellSize(const QSizeF &cell_size);
};

#endif // FIELDGRAPHICSITEM_H
