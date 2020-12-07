/* For compiling a dll on Visual C++ */
#ifdef __WIN32 
#include "pch.h"
#endif

#include "point_finder.h"
#include "point.h"
#include "rect.h"
#include <stdlib.h>
#include <stdint.h>
#include <algorithm>

using namespace std;

PointFinder::PointFinder(int size) {
    this->_size = size;
    this->_points = new const struct Point*[size];
}

PointFinder::~PointFinder() {
    delete[] this->_points;
}

void PointFinder::insert(const struct Point* point, int index) {
    struct Point* newPoint = new struct Point;
    newPoint->id = point->id;
    newPoint->rank = point->rank;
    newPoint->x = point->x;
    newPoint->y = point->y;
    this->_points[index] = newPoint;
}

const struct Point* PointFinder::getPoint(int index) {
    return this->_points[index];
}

void PointFinder::xSort() {
    pointMergeSort(this->_points, this->_size, pointLessThanX);
}

int32_t PointFinder::rectSearch(const struct Rect* rect, int32_t count, struct Point* rankedPoints) {
    int left = pointClosestGreaterIndex(this->_points, rect->lx, this->_size, xComponentLessThanValue);
    int right = pointClosestLesserIndex(this->_points, rect->hx, this->_size, valueLessThanComponentX);
    if (left == -1 || right == -1 || right < left) {
        return 0;
    }
    int newSize = 0;
    
    const struct Point** validPoints = new const struct Point*[right - left + 1];
    for (int i = 0; i < right - left + 1; i++) {
        if (this->_points[i]->y >= rect->ly && this->_points[i]->y <= rect->hy) {
            validPoints[newSize] = this->_points[i];
            newSize++;
        }
    }

    pointMergeSort(validPoints, newSize, pointLessThanRank);
    newSize = min(count, newSize);
    for (int i = 0; i < newSize; i++) {
        rankedPoints[i] = *(validPoints[i]);
    }

    delete[] validPoints;

    return newSize;
}