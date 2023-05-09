#ifndef BASICCOMPONENT_H
#define BASICCOMPONENT_H

#include <QObject>

class BasicComponent : public QObject
{
    Q_OBJECT

public:
    explicit BasicComponent(QObject *parent = nullptr);
    BasicComponent(const BasicComponent &obj) : QObject(obj.parent()) {}

    virtual BasicComponent* clone() { return new BasicComponent(*this); }
};

#endif // BASICCOMPONENT_H
