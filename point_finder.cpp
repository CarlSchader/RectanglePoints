#include "point_finder.h"
#include "point.h"
#include "rect.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
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
    this->_points[index] = point;
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

/* Testing code
These functions are not linked in the header file and will not run unless compiling point_finder.cpp as they don't contain
a global context within the scope of the project. */

struct Point* randomPoint(int8_t id) {
    struct Point* point = new Point();
    point->id = id;
    point->rank = rand() % 100;
    point->x = (float)(rand() / RAND_MAX) + (float)((rand() % 20000) - 10000);
    point->y = (float)(rand() / RAND_MAX) + (float)((rand() % 20000) - 10000);
    return point;
}

struct Rect* randomRect() {
    struct Rect* rect = new Rect();
    rect->lx = (float)(rand() / RAND_MAX) + (float)((rand() % 20000) - 10000);
    rect->hx = min((int)rect->lx + (rand() % 500), 10000);
    rect->ly = (float)(rand() / RAND_MAX) + (float)((rand() % 20000) - 10000);
    rect->hy = min((int)rect->ly + (rand() % 500), 10000);
    return rect;
}

void printPoint(struct Point* point) {
    printf("id: %d, rank: %d, x: %f y: %f\n", point->id, point->rank, point->x, point->y);
}

void printRect(struct Rect* rect) {
    printf("x: [%f, %f] y: [%f, %f]\n", rect->lx, rect->hx, rect->ly, rect->hy);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Incorrect number of command line args. (3 required)\n");
        return 1;
    }
    const int POINT_COUNT = atoi(argv[1]);
    const int RANKED_COUNT = atoi(argv[2]);
    const int RECTANGLE_COUNT = atoi(argv[3]);

    srand(time(NULL));

    PointFinder* pf = new PointFinder(POINT_COUNT); 

    time_t start = time(NULL);
    printf("\nLoading points.\n");

    for (int i = 0; i < POINT_COUNT; i++) {
        struct Point* point = randomPoint(i);
        pf->insert(point, i);
    }
    printf("Loading time: %ld\n", time(NULL) - start);

    printf("\nCreating rects.\n");
    struct Rect** rects = new struct Rect*[RECTANGLE_COUNT];
    for (int i = 0; i < RECTANGLE_COUNT; i++) {
        rects[i] = randomRect();
    }

    // printf("\nLoaded points:\n");

    // for (int i = 0; i < POINT_COUNT; i++) {
    //     printPoint(pf->getPoint(i));
    // }

    start = time(NULL);
    pf->xSort();
    printf("\nSorted points:\n");
    printf("Sorting time: %ld\n", time(NULL) - start);
    // for (int i = 0; i < POINT_COUNT; i++) {
    //     printPoint(pf->getPoint(i));
    // }


    start = time(NULL);
    struct Point rankedPoints[RANKED_COUNT];
    for (int i = 0; i < RECTANGLE_COUNT; i++) {
        int pointNumber = pf->rectSearch(rects[i], RANKED_COUNT, rankedPoints);
        // printf("\n\n%d points found inside rect:\n", pointNumber);
        // printRect(rects[i]);
        // for (int j = 0; j < pointNumber; j++) {
        //     printPoint(&rankedPoints[j]);
        // }
    }
    printf("rect searching time: %ld\n", time(NULL) - start);

    delete[] rects;

    return 0;
}