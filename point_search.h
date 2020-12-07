#ifndef POINT_SEARCH_H
#define POINT_SEARCH_H
/* Given 10 million uniquely ranked points on a 2D plane, design a datastructure and an algorithm that can find the 20
most important points inside any given rectangle. The solution has to be reasonably fast even in the worst case, while
also not using an unreasonably large amount of memory.
Create an x64 Windows DLL, that can be loaded by the test application. The DLL and the functions will be loaded
dynamically. The DLL should export the following functions: "create", "search" and "destroy". The signatures and
descriptions of these functions are given below. You can use any language or compiler, as long as the resulting DLL
implements this interface. */

/* Any unix operating systems such as linux get compiled with these directives. Compiler g++ (Doesn't build a dll)
This is how I developed because I temporarilty have a slow windows machine :-\ */
#ifdef __unix__

#define __stdcall
#define EXPORT

#endif

/* Compiling on Visual C++ on windows 64 bit */
#ifdef __WIN32

#ifdef POINT_SEARCH_EXPORTS
#define POINT_SEARCH_API __declspec(dllexport)
#else
#define POINT_SEARCH_API __declspec(import)
#endif

#define EXPORT extern "C"

#endif

/* This standard header defines the sized types used. */
#include <stdint.h>
#include "point_finder.h"

/* Declaration of the struct that is used as the context for the calls. */
struct SearchContext {
	struct PointFinder* pf;
};

EXPORT struct SearchContext* __stdcall create(const Point* points_begin, const Point* points_end);

EXPORT int32_t __stdcall search(struct SearchContext* sc, const Rect rect, const int32_t count, Point* out_points);

EXPORT struct SearchContext* __stdcall destroy(struct SearchContext* sc);

#endif