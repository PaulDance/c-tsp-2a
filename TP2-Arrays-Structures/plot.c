//
// Created by pauldance on 26/01/2020.
//

#include <stdio.h>
#include <math.h>
#include "plot.h"


void plotVerticalLine(Grid* grid, size_t j, float i0f, float i1f, char pixel) {
	for (size_t i = llrintf(i0f); i <= llrintf(i1f); i++) {
		grid->matrix[i][j] = pixel;
	}
}

void sweepPolygonAxis(Grid* grid, Point* pointsArray, size_t pointsArraySize, size_t axis, char pixel) {
	printf("sweep %lu: \n", axis);
}

void plotPolygon(Grid* grid, Point* pointsArray, size_t pointsArraySize, char pixel) {
	for (size_t j = 0; j < grid->width; j++) {
		sweepPolygonAxis(grid, pointsArray, pointsArraySize, j, pixel);
	}
}
