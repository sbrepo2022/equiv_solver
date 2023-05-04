#ifndef OBJECTCOUNTER_H
#define OBJECTCOUNTER_H

template<class T>
class ObjectCounter
{
private:
    static int objects_count;

protected:
    int id;

public:
    ObjectCounter() {
        this->id = ObjectCounter<T>::objects_count;
        ObjectCounter<T>::objects_count++;
    }

    int getId() {return this->id;}
};

template<class T>
int ObjectCounter<T>::objects_count = 1;

#endif // OBJECTCOUNTER_H
