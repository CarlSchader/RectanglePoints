#include "rect.h"
#include "point.h"

bool pointInRect(struct Point* point, struct Rect* rect) {
    return (point->x >= rect->lx && point->x <= rect->hx) && (point->y >= rect->ly && point->y <= rect->hy);
}