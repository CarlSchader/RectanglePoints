#include "point_search.h"
#include "point_alg.h"
#include <stdlib.h>
#include <stdio.h>
#include "minmax.h"

void print_point(Point point) {
    printf("Point id: %d, rank: %d, x: %f, y: %f\n", point.id, point.rank, point.x, point.y);
}

void print_points(Point* points, int n) {
    for (int i = 0; i < n; i++) {
        print_point(points[i]);
    }
}

Point make_point(int id, int rank, float x, float y) {
    Point p;
    p.id = id;
    p.rank = (int32_t)rank;
    p.x = x;
    p.y = y;
    return p;
}

SearchContext* __stdcall create(const Point* points_begin, const Point* points_end) {
    SearchContext* sc = (SearchContext*)malloc(sizeof(SearchContext));

    // int size = points_end - points_begin; // if random access iterator
    
    int size = 0; // if not random access iterator
    const Point* begin_copy = points_begin;
    while (begin_copy != points_end) {
        size++;
        begin_copy++;
    } //
    
    sc->size = size;
    sc->points = (Point*)malloc(size * sizeof(Point));
    for (int i = 0; i < size; i++) {
        sc->points[i] = *points_begin;
        points_begin++;
    }

    point_merge_sort(sc->points, size, point_less_than_x);

    return sc;
}

int32_t __stdcall search(SearchContext* sc, const Rect rect, const int32_t count, Point* out_points) {
    if (sc->size == 0 || out_points == NULL) {
        return 0;
    }

    int left = point_closest_greater_index(sc->points, rect.lx, sc->size, x_less_than_value);
    int right = point_closest_lesser_index(sc->points, rect.hx, sc->size, value_less_than_x);
    if (left == -1 || right == -1 || right < left) {
        return 0;
    }
    // printf("value: %f, found: %f\n", rect.hx, (sc->points[right]).x);

    // Point** rectangle_points = (Point**)malloc((right - left + 1) * sizeof(Point*));
    // int found_size = 0;
    // for (int i = left; i < right + 1; i++) {
    //     if (sc->points[i].y >= rect.ly && sc->points[i].y <= rect.hy) {
    //         rectangle_points[found_size] = &(sc->points[i]);
    //         found_size++;
    //     }
    // }

    Point* rectangle_points = (Point*)malloc((right - left + 1) * sizeof(Point));
    int found_size = 0;
    for (int i = left; i < right + 1; i++) {
        if (sc->points[i].y >= rect.ly && sc->points[i].y <= rect.hy) {
            rectangle_points[found_size] = sc->points[i];
            found_size++;
        }
    }

    point_k_snallest(rectangle_points, (int)count, 0, found_size - 1);

    int return_size = min(count, found_size);

    // point_quicksort(&rectangle_points[0], 0, return_size - 1);
    point_merge_sort(rectangle_points, return_size, point_less_than_rank);

    // for (int i = 0; i < return_size; i++) {
    //     out_points[i] = *(rectangle_points[i]);
    // }

    for (int i = 0; i < return_size; i++) {
        out_points[i] = rectangle_points[i];
    }

    free(rectangle_points);

    return return_size;
}

SearchContext* __stdcall destroy(SearchContext* sc) {
    free(sc->points);
    free(sc);
    return NULL;
}