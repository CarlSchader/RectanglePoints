#ifndef RECT_H
#define RECT_H

#include "point.h"

/* The following structs are packed with no padding. */
#pragma pack(push, 1)

/* Defines a rectangle, where a point (x,y) is inside, if x is in [lx, hx] and y is in [ly, hy]. */
struct Rect
{
	float lx;
	float ly;
	float hx;
	float hy;
};

#pragma pack(pop)

bool pointInRect(struct Point point, struct Rect rect);

#endif