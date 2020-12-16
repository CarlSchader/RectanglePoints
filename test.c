/* Author: Carl Schader
This main function has small unit tests for the algorithms.
Compile using gcc or g++ and run using the compiled executable. */
#if defined(__MSVS__)
#include "pch.h"
#endif

#include "point_search.h"
#include "point_alg.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define min(x, y) (((x) <= (y)) ? (x) : (y))

struct Point random_point(int id, int rank_max, float coord_max) {
    struct Point point;
    point.id = (int8_t)id;
    point.rank = rand() % rank_max;
    point.x = ((float)rand() / (float)RAND_MAX) * coord_max;
    point.y = ((float)rand() / (float)RAND_MAX) * coord_max;
    return point;
}

struct Rect random_rect(float coord_max, float rect_max_width) {
    struct Rect rect;
    rect.lx = ((float)rand() / (float)RAND_MAX) * coord_max;
    rect.hx = min(coord_max, rect.lx + rect_max_width);
    rect.ly = ((float)rand() / (float)RAND_MAX) * coord_max;
    rect.hy = min(coord_max, rect.ly + rect_max_width);
    return rect;
}

void print_search_result(struct Rect rect, int32_t count, struct Point* out_points) {
    printf("\nSearch results::\n");
    printf("Rect: x: [%.1f, %.1f] y: [%.1f, %.1f]\n", rect.lx, rect.hx, rect.ly, rect.hy);
    printf("Result count: %d\n", count);
    print_points(out_points, count);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("3 args required: ./test [POINT_COUNT] [RECT_COUNT] [RESULT_COUNT]\n");
        return -1;
    }
    int POINT_COUNT = atoi(argv[1]);
    int RECT_COUNT = atoi(argv[2]);
    int RESULT_COUNT = atoi(argv[3]);
    int RANK_MAX = 100;
    float COORD_MAX = 10000;
    float RECT_MAX_WIDTH = 1000;

    // srand(time(NULL));
    srand(0);
    time_t start;

    printf("Loading points:\n\n");
    struct Point* input_points = (struct Point*)malloc(POINT_COUNT * sizeof(struct Point));
    for (int i = 0; i < POINT_COUNT; i++) {
        input_points[i] = random_point(i, RANK_MAX, COORD_MAX);
    }

    // input_points[0] = make_point(0, 97, 3081.0, 9141.0);
    // input_points[1] = make_point(1, 89, 8499.0, 6219.0);
    // input_points[2] = make_point(2, 84, 1389.0, 3256.0);
    // input_points[3] = make_point(3, 15, 4236.0, 316.0);

    // test_merge(&input_points[0], 0, 1, 3);

    // test_merge_sort(input_points, POINT_COUNT, 20);
    // test_closest_greater_index(input_points, POINT_COUNT, 1000.0);
    // test_closest_lesser_index(input_points, POINT_COUNT, 1000.0);

    printf("Testing create:\n");
    start = time(NULL);
    struct SearchContext* sc = create(&input_points[0], &input_points[POINT_COUNT]);
    printf("Time: %ld\n\n", time(NULL) - start);
    
    free(input_points);

    printf("Loading rects:\n\n");
    struct Rect* rects = (struct Rect*)malloc(RECT_COUNT * sizeof(struct Rect));
    for (int i = 0; i < RECT_COUNT; i++) {
        rects[i] = random_rect(COORD_MAX, RECT_MAX_WIDTH);
    }

    printf("Testing search:\n");
    start = time(NULL);
    struct Point* out_points = (struct Point*)malloc(RESULT_COUNT * sizeof(struct Point));
    int count = 0;
    for (int i = 0; i < RECT_COUNT; i++) {
        count = search(sc, rects[i], RESULT_COUNT, out_points);
        // print_search_result(rects[i], count, out_points);
    }
    printf("Time: %ld\n\n", time(NULL) - start);

    print_search_result(rects[RECT_COUNT - 1], count, out_points);

    printf("Testing destroy:\n");
    start = time(NULL);
    destroy(sc);
    printf("Time: %ld\n\n", time(NULL) - start);

    return 0;
}