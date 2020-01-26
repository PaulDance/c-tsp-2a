//
// Created by pauldance on 26/01/2020.
//

#include <glob.h>
#include "grid.h"


#ifndef TP2_ARRAYS_STRUCTURES_PLOT_H
#define TP2_ARRAYS_STRUCTURES_PLOT_H

/**
 * Defines a 2D point with single floating precision
 * on the usual top-left indirect geometric frame.
 */
typedef struct Point {
	/**
	 * The ordinate of the Point, origin at the top.
	 */
	float i;
	/**
	 * The abscissa of the Point, origin on the left.
	 */
	float j;
} Point;

/**
 * Represents a 2D polygon via its vertices.
 */
typedef struct Polygon {
	/**
	 * The size of the Polygon in number of vertices.
	 */
	size_t size;
	/**
	 * The array of vertices forming the Polygon, as a pointer.
	 */
	Point* vertices;
} Polygon;

void plotPolygon(Grid* grid, Polygon polygon, char pixel);
void plotTriangle(Grid* grid, Point p1, Point p2, Point p3, char pixel);
void plotSierpinskiTriangle(Grid* grid, Point p1, Point p2, Point p3, int level, char pixel);

#endif //TP2_ARRAYS_STRUCTURES_PLOT_H
