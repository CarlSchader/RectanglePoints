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

struct SearchContext* __stdcall create(const struct Point* points_begin, const struct Point* points_end) {
    struct SearchContext* sc = (struct SearchContext*)malloc(sizeof(struct SearchContext));

    // int size = points_end - points_begin; // if random access iterator
    
    int size = 0; // if not random access iterator
    const struct Point* begin_copy = points_begin;
    while (begin_copy != points_end) {
        size++;
        begin_copy++;
    } //
    
    sc->size = size;
    sc->points = (struct Point*)malloc(size * sizeof(struct Point));
    for (int i = 0; i < size; i++) {
        sc->points[i] = *points_begin;
        points_begin++;
    }

    point_merge_sort(sc->points, size, point_less_than_x);

    return sc;
}

int32_t __stdcall search(struct SearchContext* sc, const struct Rect rect, const int32_t count, struct Point* out_points) {
    if (sc->size == 0 || out_points == NULL) {
        return 0;
    }

    int left = point_closest_greater_index(sc->points, rect.lx, sc->size, x_less_than_value);
    int right = point_closest_lesser_index(sc->points, rect.hx, sc->size, value_less_than_x);
    if (left == -1 || right == -1 || right < left) {
        return 0;
    }

    struct Point* rectangle_points = (struct Point*)malloc((right - left + 1) * sizeof(struct Point));
    int found_size = 0;
    for (int i = left; i < right + 1; i++) {
        if (sc->points[i].y >= rect.ly && sc->points[i].y <= rect.hy) {
            rectangle_points[found_size] = sc->points[i];
            found_size++;
        }
    }

    // int return_size = min(count, found_size);

    // if (count < found_size) {
    //     point_k_smallest(rectangle_points, (int)count, 0, found_size - 1);
    //     printf("After k smallest\n");
    //     for (int i = 0; i < count; i++) {
    //         print_point(rectangle_points[i]);
    //     }
    //     point_merge_sort(rectangle_points, count, point_less_than_rank);
    //     printf("After merge\n");
    //     for (int i = 0; i < count; i++) {
    //         print_point(rectangle_points[i]);
    //     }
    //     for (int i = 0; i < count; i++) {
    //         out_points[i] = rectangle_points[i];
    //     }
    //     free(rectangle_points);
        
    //     return count;
    // }
    // else {
    //     point_merge_sort(rectangle_points, found_size, point_less_than_rank);
    //     for (int i = 0; i < found_size; i++) {
    //         out_points[i] = rectangle_points[i];
    //     }
    //     free(rectangle_points);
    //     return found_size;
    // }

    point_merge_sort(rectangle_points, found_size, point_less_than_rank);
    for (int i = 0; i < min(found_size, count); i++) {
        out_points[i] = rectangle_points[i];
    }
    printf("After merge\n");
    for (int i = 0; i < min(found_size, count); i++) {
        print_point(rectangle_points[i]);
    }
    free(rectangle_points);
    return min(found_size, count);

    // printf("After k smallest\n");
    // for (int i = 0; i < return_size; i++) {
    //     print_point(rectangle_points[i]);
    // }

    // printf("After merge\n");
    // for (int i = 0; i < min(found_size, count); i++) {
    //     print_point(rectangle_points[i]);
    // }

    

    // for (int i = 0; i < return_size; i++) {
    //     print_point(out_points[i]);
    // }
    // printf("rect: x %.2f x %.2f y %.2f y %.2f\n", rect.lx, rect.hx, rect.ly, rect.hy);

    // free(rectangle_points);

    // return return_size;
}

struct SearchContext* __stdcall destroy(struct SearchContext* sc) {
    free(sc->points);
    free(sc);
    return NULL;
}