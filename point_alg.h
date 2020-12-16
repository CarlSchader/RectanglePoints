#ifndef POINT_H
#define POINT_H

#include "point_search.h"
#include <stdint.h>
#include <stdbool.h>

typedef bool (*pointLessThanOp)(const struct Point*, const struct Point*);

typedef bool (*componentLessThanValue)(const struct Point*, float);

typedef bool (*valueLessThanComponent)(float, const struct Point*);

void point_merge_sort(struct Point* points, int size, pointLessThanOp less_than);

void point_merge(struct Point* points, struct Point* buffer, int left, int middle, int right, pointLessThanOp less_than);

int point_closest_greater_index(struct Point* points, float searchValue, int size, componentLessThanValue less_than);

int point_closest_lesser_index(struct Point* points, float searchValue, int size, valueLessThanComponent less_than);

void point_k_smallest(struct Point* points, int k, int left, int right);

void point_quicksort(struct Point* points, int left, int right);

int point_partition(struct Point* points, int left, int right);

void point_radix_rank(struct Point* points, int size);

void count_sort_128(struct Point* points, int size);

void count_sort_stack(struct Point* points, int left, int right);

void count_sort_heap(struct Point* points, int left, int right);

bool point_less_than_x(const struct Point* p1, const struct Point* p2);

bool point_less_than_y(const struct Point* p1, const struct Point* p2);

bool point_less_than_rank(const struct Point* p1, const struct Point* p2);

bool x_less_than_value(const struct Point* point, float value);

bool y_less_than_value(const struct Point* point, float value);

bool value_less_than_x(float value, const struct Point* point);

bool value_less_than_y(float value, const struct Point* point);

#endif