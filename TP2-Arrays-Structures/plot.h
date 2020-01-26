//
// Created by pauldance on 26/01/2020.
//

#include <glob.h>
#include "grid.h"


#ifndef TP2_ARRAYS_STRUCTURES_PLOT_H
#define TP2_ARRAYS_STRUCTURES_PLOT_H

typedef struct Point {
	size_t i;
	size_t j;
} Point;

void plotVerticalLine(Grid* grid, size_t j, float i0f, float i1f, char pixel);
void sweepPolygonAxis(Grid* grid, Point* pointsArray, size_t pointsArraySize, size_t axis, char pixel);
void plotPolygon(Grid* grid, Point* pointsArray, size_t pointsArraySize, char pixel);

#endif //TP2_ARRAYS_STRUCTURES_PLOT_H
