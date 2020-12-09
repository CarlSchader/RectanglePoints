#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include "point_search.h"

typedef bool (*pointLessThanOp)(const Point*, const Point*);

typedef bool (*componentLessThanValue)(const Point*, float);

typedef bool (*valueLessThanComponent)(float, const Point*);

void point_merge_sort(Point* points, int size, pointLessThanOp less_than);
void point_merge_sort(Point** points, int size, pointLessThanOp less_than);

void point_merge(Point* points, Point* buffer, int left, int middle, int right, pointLessThanOp less_than);
void point_merge(Point** points, Point** buffer, int left, int middle, int right, pointLessThanOp less_than);

int point_closest_greater_index(Point* points, float searchValue, int size, componentLessThanValue less_than);

int point_closest_lesser_index(Point* points, float searchValue, int size, valueLessThanComponent less_than);

void point_k_snallest(Point* points, int k, int left, int right);
void point_k_snallest(Point** points, int k, int left, int right);

void point_quicksort(Point* points, int left, int right);
void point_quicksort(Point** points, int left, int right);

int point_partition(Point* points, int left, int right);
int point_partition(Point** points, int left, int right);

bool point_less_than_x(const Point* p1, const Point* p2);

bool point_less_than_y(const Point* p1, const Point* p2);

bool point_less_than_rank(const Point* p1, const Point* p2);

bool x_less_than_value(const Point* point, float value);

bool y_less_than_value(const Point* point, float value);

bool value_less_than_x(float value, const Point* point);

bool value_less_than_y(float value, const Point* point);

#endif