/* For compiling a dll on Visual C++ */
#ifdef __WIN32 
#include "pch.h"
#endif

#include "rect.h"
#include "point.h"

bool pointInRect(const struct Point* point, const struct Rect* rect) {
    return (point->x >= rect->lx && point->x <= rect->hx) && (point->y >= rect->ly && point->y <= rect->hy);
}