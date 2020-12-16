/* Author: Carl Schader
Function definitions for the three functions the DLL must export. */
#if defined(__MSVS__)
#include "pch.h"
#endif

#include "point_search.h"
#include "point_alg.h"
#include <stdlib.h>
#include <stdio.h>

#define min(x, y) (((x) <= (y)) ? (x) : (y))

void print_point(struct Point point) {
    printf("Point id: %d, rank: %d, x: %f, y: %f\n", point.id, point.rank, point.x, point.y);
}

void print_points(struct Point* points, int n) {
    for (int i = 0; i < n; i++) {
        print_point(points[i]);
    }
}

struct Point make_point(int id, int rank, float x, float y) {
    struct Point p;
    p.id = id;
    p.rank = (int32_t)rank;
    p.x = x;
    p.y = y;
    return p;
}

int rankcompare(const void* p1, const void* p2) {
    return (*((struct Point*)p1)).rank - (*((struct Point*)p2)).rank;
}

struct SearchContext* __stdcall create(const struct Point* points_begin, const struct Point* points_end) {
    struct SearchContext* sc = (struct SearchContext*)malloc(sizeof(struct SearchContext));

    int size = points_end - points_begin; // if random access iterator
    
    // int size = 0; // if not random access iterator
    // const struct Point* begin_copy = points_begin;
    // while (begin_copy != points_end) {
    //     size++;
    //     begin_copy++;
    // } //
    
    sc->size = size;
    sc->pointsx = (struct Point*)malloc(size * sizeof(struct Point));
    sc->pointsy = (struct Point*)malloc(size * sizeof(struct Point));
    for (int i = 0; i < size; i++) {
        sc->pointsx[i] = *points_begin;
        sc->pointsy[i] = *points_begin;
        points_begin++;
    }

    point_merge_sort_x(sc->pointsx, size);
    point_merge_sort_y(sc->pointsy, size);

    return sc;
}

int32_t __stdcall search(struct SearchContext* sc, const struct Rect rect, const int32_t count, struct Point* out_points) {
    if (sc->size == 0 || out_points == NULL) {
        return 0;
    }

    // bool finding_y = rect.hx - rect.lx <= rect.hy - rect.ly;
    int lefty = point_closest_greater_index_y(sc->pointsy, rect.ly, sc->size);
    int righty = point_closest_lesser_index_y(sc->pointsy, rect.hy, sc->size);
    int leftx = point_closest_greater_index_x(sc->pointsx, rect.lx, sc->size);
    int rightx = point_closest_lesser_index_x(sc->pointsx, rect.hx, sc->size);

    struct Point* rectangle_points;
    int found_size;

    if (rightx - leftx + 1 < righty - lefty + 1) {
        if (leftx == -1 || rightx == -1 || rightx < leftx) {
            return 0;
        }

        rectangle_points = (struct Point*)malloc((rightx - leftx + 1) * sizeof(struct Point));
        found_size = 0;
        for (int i = leftx; i < rightx + 1; i++) {
            if (sc->pointsx[i].y >= rect.ly && sc->pointsx[i].y <= rect.hy) {
                rectangle_points[found_size] = sc->pointsx[i];
                found_size++;
            }
        }
    }
    else {
        if (lefty == -1 || righty == -1 || righty < lefty) {
            return 0;
        }
        rectangle_points = (struct Point*)malloc((righty - lefty + 1) * sizeof(struct Point));
        found_size = 0;
        for (int i = lefty; i < righty + 1; i++) {
            if (sc->pointsy[i].x >= rect.lx && sc->pointsy[i].x <= rect.hx) {
                rectangle_points[found_size] = sc->pointsy[i];
                found_size++;
            }
        }
    }

    if (count < found_size) {
        point_k_smallest(rectangle_points, (int)count, 0, found_size - 1);
        point_merge_sort_rank(rectangle_points, count + 1);
        for (int i = 0; i < count; i++) {
            out_points[i] = rectangle_points[i];
        }
        free(rectangle_points);
        return count;
    }
    else {
        point_merge_sort_rank(rectangle_points, found_size + 1);
        for (int i = 0; i < found_size; i++) {
            out_points[i] = rectangle_points[i];
        }
        free(rectangle_points);
        return found_size;
    }
}

struct SearchContext* __stdcall destroy(struct SearchContext* sc) {
    free(sc->pointsx);
    free(sc->pointsy);
    free(sc);
    return NULL;
}