#include "point_finder.h"
#include "point_search.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

PointFinder::PointFinder(int size) {
    this->_size = size;
    this->_points = new struct Point[size];
}

PointFinder::~PointFinder() {
    delete[] this->_points;
    // delete[] this->_rectanglePoints;
}

void PointFinder::insert(struct Point point, int index) {
    this->_points[index] = point;
}

struct Point PointFinder::getPoint(int index) {
    return this->_points[index];
}

struct Point* PointFinder::searchRect() {
    return this->_points;
}

void PointFinder::_pointMergeSort(struct Point* points, int size, bool (*pointLessThanOp)(struct Point p1, struct Point p2)) {
    int left, middle, right;
    Point buffer;
    left = 0;
    middle = 1;
    right = 1;

    do {
        this->_pointMerge(p)
    }
    while()
}

// middle is the index of the last element of the left array.
void PointFinder::_pointMerge(struct Point* points, int left, int middle, int right, bool (*pointLessThanOp)(struct Point p1, struct Point p2)) {
    Point leftArray[middle - left + 1];
    Point rightArray[right - middle];

    for (int i = left; i < middle - left + 1; i++) {
        leftArray[i] = points[i];
    }

    for (int i = middle + 1; i < right - middle; i++) {
        rightArray[i] = points[i];
    }

    int i, j = left, middle + 1;
    while (i < middle + 1 && j < right + 1) {
        
    }

}

bool PointFinder::_xLessThan(struct Point p1, struct Point p2) {
    return p1.x < p2.x;
}

bool PointFinder::_yLessThan(struct Point p1, struct Point p2) {
    return p1.y < p2.y;
}

/* Testing code
These functions are not linked in the header file and will not run unless compiling point_finder.cpp as they don't contain
a global context within the scope of the project. */

struct Point randomPoint(int8_t id) {
    struct Point point;
    point.id = id;
    point.rank = rand() % 100;
    point.x = (float)(rand() / RAND_MAX) + (float)((rand() % 20000) - 10000);
    point.y = (float)(rand() / RAND_MAX) + (float)((rand() % 20000) - 10000);
    return point;
}

void printPoint(struct Point point) {
    printf("id: %d, rank: %d, x: %f y: %f\n", point.id, point.rank, point.x, point.y);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Incorrect number of command line args. (3 required)\n");
        return 1;
    }
    const int POINT_COUNT = atoi(argv[1]);
    const int RANKED_COUNT = atoi(argv[2]);
    const int RECTANGLE_COUNT = atoi(argv[3]);

    PointFinder pf = PointFinder(POINT_COUNT); 
    for (int i = 0; i < POINT_COUNT; i++) {
        struct Point point = randomPoint(i);
        pf.insert(point, i);
    }

    for (int i = 0; i < POINT_COUNT; i++) {
        printPoint(pf.getPoint(i));
    }
    
    return 0;
}