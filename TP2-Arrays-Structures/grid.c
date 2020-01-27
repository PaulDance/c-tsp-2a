//
// Created by pauldance on 25/01/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "grid.h"


/**
 * Initializes the given grid to hold a new matrix of specified
 * dimensions where all positions are filled with the same value.
 * 
 * @param grid The reference to a not-yet-initialized Grid structure
 *				value as a pointer.
 * @param width The desired width in number of elements.
 * @param height The desired height in number of elements.
 * @param pixel The character value to put in all positions.
 */
void initGrid(Grid* grid, size_t width, size_t height, char pixel) {
	grid->width = width;
	grid->height = height;
	grid->matrix = (char**) malloc(grid->height * sizeof(char*));
	
	for (size_t i = 0; i < grid->height; i++) {
		grid->matrix[i] = (char*) malloc(grid->width * sizeof(char));
		
		for (size_t j = 0; j < grid->width; j++) {
			grid->matrix[i][j] = pixel;
		}
	}
}

/**
 * Creates and returns a new initialized Grid structure value.
 * 
 * @param width The desired width in number of elements.
 * @param height The desired height in number of elements.
 * @param pixel The character value to put in all positions.
 * @return The pointer to the new Grid value.
 */
Grid* newGrid(size_t width, size_t height, char pixel) {
	Grid* grid = (Grid*) malloc(sizeof(Grid));
	initGrid(grid, width, height, pixel);
	return grid;
}

/**
 * Prints the given Grid structure value to stdout in an
 * indirect frame, i.e. the x axis is from top left to top
 * right and the y axis is from top left to bottom left.
 * 
 * @param grid The pointer to the Grid to print.
 */
void printGrid(Grid* grid) {
	for (size_t i = 0; i < grid->height; i++) {
		for (size_t j = 0; j < grid->width; j++) {
			putchar(grid->matrix[i][j]);
		}
		
		puts("");
	}
}

/**
 * Frees the memory spaces occupied by the given Grid.
 * @param grid The pointer to the Grid structure value.
 */
void freeGrid(Grid* grid) {
	for (size_t i = 0; i < grid->height; i++) {
		free(grid->matrix[i]);
	}
	
	free(grid->matrix);
	free(grid);
}
