#ifndef POINT_FINDER_H
#define POINT_FINDER_H

#include "point.h"
#include "rect.h"
#include <stdint.h>

class PointFinder {
    public:
        PointFinder(int size);
        ~PointFinder();
        void insert(struct Point, int index);
        struct Point getPoint(int index);
        struct Point* searchRect();
        void xSort();
        int32_t rectSearch(struct Rect rect, int32_t count, struct Point* rankedPoints);

    private:
        struct Point* _points;
        int _size;
};

#endif