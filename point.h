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

void pointMergeSort(struct Point** points, int size, bool (*pointLessThanOp)(struct Point*, struct Point*));

void pointMerge(struct Point** points, int left, int middle, int right, bool (*pointLessThanOp)(struct Point*, struct Point*));

int pointClosestGreaterIndex(struct Point** points, float searchValue, int size, bool (*componentLessThanValue)(struct Point*, float));

int pointClosestLesserIndex(struct Point** points, float searchValue, int size, bool (*valueLessThanComponent)(float, struct Point*));

bool pointLessThanX(struct Point* p1, struct Point* p2);

bool pointLessThanY(struct Point* p1, struct Point* p2);

bool pointLessThanRank(struct Point* p1, struct Point* p2);

bool xComponentLessThanValue(struct Point* point, float value);

bool yComponentLessThanValue(struct Point* point, float value);

bool valueLessThanComponentX(float value, struct Point* point);

bool valueLessThanComponentY(float value, struct Point* point);

#endif