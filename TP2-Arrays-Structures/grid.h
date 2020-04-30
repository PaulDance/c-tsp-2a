#ifndef TP2_ARRAYS_STRUCTURES_GRID_H
#define TP2_ARRAYS_STRUCTURES_GRID_H

/**
 * Defines a 2D matrix of characters along with its
 * associated width and height.
 */
typedef struct Grid {
    /**
     * The width of the Grid in number of elements.
     */
    size_t width;
    /**
     * The height of the Grid in number of elements.
     */
    size_t height;
    /**
     * The matrix of character elements that actually
     * makes up the important part of the Grid.
     */
    char** matrix;
} Grid;

Grid* newGrid(size_t width, size_t height, char pixel);

void initGrid(Grid* grid, size_t width, size_t height, char pixel);

void printGrid(Grid* grid);

void freeGrid(Grid* grid);

#endif //TP2_ARRAYS_STRUCTURES_GRID_H
