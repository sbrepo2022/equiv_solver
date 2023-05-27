#ifndef QPOINT_HASH_H
#define QPOINT_HASH_H

#include <QPoint>
#include <QHash>

inline bool operator==(QPoint &p1, QPoint &p2)
{
    return p1.x() == p2.x() && p1.y() == p2.y();
}

//inline size_t qHash(const QPoint &key)
//{
//    return qHash(QPair<int, int>(key.x(), key.y()));
//}

inline bool operator==(QPointF &p1, QPointF &p2)
{
    return p1.x() == p2.x() && p1.y() == p2.y();
}

//inline size_t qHash(const QPointF &key)
//{
//    return qHash(QPair<qreal, qreal>(key.x(), key.y()));
//}

namespace std {
template <> struct hash<QPointF>
{
    // seed is optional
    size_t operator()(const QPointF &key, size_t seed) const {return qHashMulti(seed, key.x(), key.y());}
};

template <> struct hash<QPoint>
{
    // seed is optional
    size_t operator()(const QPoint &key, size_t seed) const {return qHashMulti(seed, key.x(), key.y());}
};
}

#endif
