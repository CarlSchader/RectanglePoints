#ifndef POINT_H
#define POINT_H

#include "point_search.h"
#include <stdint.h>
#include <stdbool.h>

void point_merge_sort_x(struct Point* points, int size);

void point_merge_sort_y(struct Point* points, int size);

void point_merge_sort_rank(struct Point* points, int size);

int point_closest_greater_index_x(struct Point* points, float searchValue, int size);

int point_closest_lesser_index_x(struct Point* points, float searchValue, int size);

int point_closest_greater_index_y(struct Point* points, float searchValue, int size);

int point_closest_lesser_index_y(struct Point* points, float searchValue, int size);

void point_k_smallest(struct Point* points, int k, int left, int right);

int point_partition(struct Point* points, int left, int right);

#endif