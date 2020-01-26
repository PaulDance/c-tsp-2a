#include "sort.h"
#include "grid.h"
#include "plot.h"


int main() {
	Grid* grid = newGrid(129, 65, ' ');
	
	plotSierpinskiTriangle(grid, (Point) {0, 128}, (Point) {64, 0}, (Point) {64, 128}, 6, '*');
	plotSierpinskiTriangle(grid, (Point) {0, 0}, (Point) {64, 0}, (Point) {0, 128}, 6, '*');
	
	printGrid(grid);
	freeGrid(grid);
	return 0;
}
