#ifndef POINT_FINDER_H
#define POINT_FINDER_H

#include "point.h"
#include "rect.h"
#include <stdint.h>

class PointFinder {
    public:
        PointFinder(int size);
        ~PointFinder();
        void insert(const struct Point*, int index);
        const struct Point* getPoint(int index);
        void xSort();
        int32_t rectSearch(const struct Rect* rect, int32_t count, struct Point* rankedPoints);

    private:
        const struct Point** _points;
        int _size;
};

#endif