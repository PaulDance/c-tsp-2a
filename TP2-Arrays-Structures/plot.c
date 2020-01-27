//
// Created by pauldance on 26/01/2020.
//

#include <math.h>
#include "plot.h"
#include "sort.h"


/**
 * Computes the middle point of the line joining two given points.
 * 
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The middle point.
 */
Point lineMiddlePoint(Point p1, Point p2) {
	return (Point) {(p1.i + p2.i) / 2, (p1.j + p2.j) / 2};
}

/**
 * Draws a vertical line on the given axis between two ordinates.
 * 
 * @param grid The grid to draw on as a pointer.
 * @param j The abscissa of the vertical axis the line should be on.
 * @param i0f The ordinate of the first point as float. Must be less
 * 				than or equals to i1f. A rounding will be performed.
 * @param i1f The ordinate of the second point as float. Must be greater
 * 				than or equals to i1f. A rounding will be performed.
 * @param pixel The pixel to draw with.
 */
void plotVerticalLine(Grid* grid, size_t j, float i0f, float i1f, char pixel) {
	size_t i1 = (size_t) llrintf(i1f);
	
	for (size_t i = (size_t) llrintf(i0f); i <= i1; i++) {
		grid->matrix[i][j] = pixel;
	}
}

/**
 * Sweeps a polygon vertically on the given axis in order to find
 * the potential intersections between its sides and the axis to
 * then draw the vertical lines and fill the inner area on the axis.
 * 
 * @param grid The grid to draw on as a pointer.
 * @param polygon The polygon to draw.
 * @param axis The abscissa of the vertical axis the sweeping should
 * 				be done on.
 * @param pixel The pixel to draw with.
 */
void sweepPolygonAxis(Grid* grid, Polygon polygon, size_t axis, char pixel) {
	float intersOrds[polygon.size];
	size_t lastPointIndex = 0;
	size_t j = polygon.size - 1;
	
	for (size_t i = 0; i < polygon.size; i++) {											// Iterating over pairs of polygon points,
		if (polygon.vertices[i].j == axis) {
			if (polygon.vertices[j].j == axis) {										// if they are vertically aligned,
				if (polygon.vertices[i].i < polygon.vertices[j].i) {					// plot the corresponding line directly;
					plotVerticalLine(grid, axis, polygon.vertices[i].i, polygon.vertices[j].i, pixel);
				}
				else {
					plotVerticalLine(grid, axis, polygon.vertices[j].i, polygon.vertices[i].i, pixel);
				}
			}
			else {																		// otherwise, it's just a corner point,
				grid->matrix[llrintf(polygon.vertices[i].i)][axis] = pixel;				// so plot it directly as well;
			}
		}
		
		if ((polygon.vertices[i].j <= axis && axis < polygon.vertices[j].j)				// in any case,
				|| (polygon.vertices[j].j <= axis && axis < polygon.vertices[i].j)) {	// if the polygon side intersects with the axis,
			insertValue(intersOrds, lastPointIndex,
						polygon.vertices[i].i + (axis - polygon.vertices[i].j)	// insert its ordinate in a sorted manner;
							* (polygon.vertices[j].i - polygon.vertices[i].i)
							/ (polygon.vertices[j].j - polygon.vertices[i].j));
			lastPointIndex++;
		}
		
		j = i;
	}
	
	if (lastPointIndex != 0UL) {
		for (size_t i = 0; i < lastPointIndex - 1; i += 2) {							// finally, fill the polygon vertically.
			plotVerticalLine(grid, axis, intersOrds[i], intersOrds[i + 1], pixel);
		}
	}
}

/**
 * Plots the given polygon with a filled inner area.
 * 
 * @param grid The grid to draw on as a pointer.
 * @param polygon The polygon to draw.
 * @param pixel The pixel to draw with.
 */
void plotPolygon(Grid* grid, Polygon polygon, char pixel) {
	for (size_t j = 0; j < grid->width; j++) {
		sweepPolygonAxis(grid, polygon, j, pixel);
	}
}

/**
 * Plots a triangle using its three vertices. Order doesn't matter.
 * 
 * @param grid The grid to draw on as a pointer.
 * @param p1 The first point.
 * @param p2 The second point.
 * @param p3 The third point.
 * @param pixel The pixel to draw with.
 */
void plotTriangle(Grid* grid, Point p1, Point p2, Point p3, char pixel) {
	plotPolygon(grid, (Polygon) {3, (Point[]) {p1, p2, p3}}, pixel);
}

/**
 * Plots a Sierpinski triangle using its three base vertices and
 * a level. Order of the points doesn't matter.
 * 
 * @param grid The grid to draw on as a pointer.
 * @param p1 The first point.
 * @param p2 The second point.
 * @param p3 The third point.
 * @param level The number of iterations the algorithm should perform.
 * @param pixel The pixel to draw with.
 */
void plotSierpinskiTriangle(Grid* grid, Point p1, Point p2, Point p3, int level, char pixel) {
	if (level == 1) {
		plotTriangle(grid, p1, p2, p3, pixel);
	}
	else {
		plotSierpinskiTriangle(grid, p1, lineMiddlePoint(p1, p2), lineMiddlePoint(p3, p1), level - 1, pixel);
		plotSierpinskiTriangle(grid, lineMiddlePoint(p1, p2), p2, lineMiddlePoint(p2, p3), level - 1, pixel);
		plotSierpinskiTriangle(grid, lineMiddlePoint(p3, p1), lineMiddlePoint(p2, p3), p3, level - 1, pixel);
	}
}

