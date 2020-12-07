#ifndef POINT_H
#define POINT_H

#include <stdint.h>

/* The following structs are packed with no padding. */
#pragma pack(push, 1)

/* Defines a point in 2D space with some additional attributes like id and rank. */
struct Point
{
	int8_t id;
	int32_t rank;
	float x;
	float y;
};

#pragma pack(pop)

void pointMergeSort(const struct Point** points, int size, bool (*pointLessThanOp)(const struct Point*, const struct Point*));

void pointMerge(const struct Point** points, int left, int middle, int right, bool (*pointLessThanOp)(const struct Point*, const struct Point*));

int pointClosestGreaterIndex(const struct Point** points, float searchValue, int size, bool (*componentLessThanValue)(const struct Point*, float));

int pointClosestLesserIndex(const struct Point** points, float searchValue, int size, bool (*valueLessThanComponent)(float, const struct Point*));

bool pointLessThanX(const struct Point* p1, const struct Point* p2);

bool pointLessThanY(const struct Point* p1, const struct Point* p2);

bool pointLessThanRank(const struct Point* p1, const struct Point* p2);

bool xComponentLessThanValue(const struct Point* point, float value);

bool yComponentLessThanValue(const struct Point* point, float value);

bool valueLessThanComponentX(float value, const struct Point* point);

bool valueLessThanComponentY(float value, const struct Point* point);

#endif