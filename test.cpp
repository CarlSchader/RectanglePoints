/* For compiling a dll on Visual C++ */
#ifdef __WIN64 
#include "pch.h"
#endif

#include "point_finder.h"
#include "point.h"
#include "rect.h"
#include "point_search.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>

using namespace std;

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
        printf("Incorrect number of command line args. (3 required) [POINT_COUNT] [RECT_COUNT] [RANKED_COUNT] \n");
        return 1;
    }
    const int POINT_COUNT = atoi(argv[1]);
    const int RECTANGLE_COUNT = atoi(argv[2]);
    const int RANKED_COUNT = atoi(argv[3]);

    srand(time(NULL));

    printf("%d Testing create\n", 0);
    struct Point* points = new struct Point[POINT_COUNT];
    for (int i = 0; i < POINT_COUNT; i++) {
        points[i] = *randomPoint(i);
    }
    struct SearchContext* sc = create(&points[0], &points[POINT_COUNT]);
    delete[] points;


    printf("%d Testing search\n", 1);
    struct Rect* rects = new struct Rect[RECTANGLE_COUNT];
    for (int i = 0; i < RECTANGLE_COUNT; i++) {
        rects[i] = *randomRect();
    }

    struct Point* out_points = new struct Point[RANKED_COUNT];
    for (int i = 0; i < RECTANGLE_COUNT; i++) {
        search(sc, rects[i], RANKED_COUNT, out_points);
    }
    delete[] out_points;
    delete[] rects;


    //

    // PointFinder* pf = new PointFinder(POINT_COUNT); 

    // time_t start = time(NULL);
    // printf("\nLoading points.\n");

    // for (int i = 0; i < POINT_COUNT; i++) {
    //     struct Point* point = randomPoint(i);
    //     pf->insert(point, i);
    // }
    // printf("Loading time: %ld\n", time(NULL) - start);

    // printf("\nCreating rects.\n");
    // struct Rect** rects = new struct Rect*[RECTANGLE_COUNT];
    // for (int i = 0; i < RECTANGLE_COUNT; i++) {
    //     rects[i] = randomRect();
    // }

    // // printf("\nLoaded points:\n");

    // // for (int i = 0; i < POINT_COUNT; i++) {
    // //     printPoint(pf->getPoint(i));
    // // }

    // start = time(NULL);
    // pf->xSort();
    // printf("\nSorted points:\n");
    // printf("Sorting time: %ld\n", time(NULL) - start);
    // // for (int i = 0; i < POINT_COUNT; i++) {
    // //     printPoint(pf->getPoint(i));
    // // }


    // start = time(NULL);
    // struct Point rankedPoints[RANKED_COUNT];
    // for (int i = 0; i < RECTANGLE_COUNT; i++) {
    //     int pointNumber = pf->rectSearch(rects[i], RANKED_COUNT, rankedPoints);
    //     // printf("\n\n%d points found inside rect:\n", pointNumber);
    //     // printRect(rects[i]);
    //     // for (int j = 0; j < pointNumber; j++) {
    //     //     printPoint(&rankedPoints[j]);
    //     // }
    // }
    // printf("rect searching time: %ld\n", time(NULL) - start);

    // delete[] rects;

    return 0;
}