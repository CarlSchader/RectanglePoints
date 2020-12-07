/* For compiling a dll on Visual C++ */
#ifdef __WIN32 
#include "pch.h"
#endif

#include "point_search.h"
#include "point_finder.h"
#include "point.h"
#include "rect.h"
#include <stdint.h>
#include <iterator>

using namespace std;

struct SearchContext* __stdcall create(const Point* points_begin, const Point* points_end) {
    struct SearchContext* sc = new struct SearchContext();
    int pointCount = distance(points_begin, points_end);

    sc->pf = new PointFinder(pointCount);
    for (int i = 0; i < pointCount; i++) {
        sc->pf->insert(points_begin, i);
        points_begin++;
    }

    sc->pf->xSort();
    return sc;
}

int32_t __stdcall search(struct SearchContext* sc, const Rect rect, const int32_t count, Point* out_points) {
    return (int32_t)sc->pf->rectSearch(&rect, count, out_points);
}

struct SearchContext* __stdcall destroy(struct SearchContext* sc) {
    try {
        delete sc->pf;
        delete sc;
    }
    catch (int e) {
        return sc;
    }
    return nullptr;
}