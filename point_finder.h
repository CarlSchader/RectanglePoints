#ifndef POINT_FINDER_H
#define POINT_FINDER_H

#include "point_search.h"

class PointFinder {
    public:
        PointFinder(int size);
        ~PointFinder();
        void insert(struct Point, int index);
        struct Point getPoint(int index);

        struct Point* searchRect();

    private:
        void _pointMergeSort(struct Point* points, int size, bool (*pointLessThanOp)(struct Point p1, struct Point p2));
        void _pointMerge(struct Point* points, int left, int middle, int right, bool (*pointLessThanOp)(struct Point p1, struct Point p2));
        bool _xLessThan(struct Point point1, struct Point point2);
        bool _yLessThan(struct Point point1, struct Point point2);

        struct Point* _points;
        struct Point* _rectanglePoints;
        int _size;
};

#endif