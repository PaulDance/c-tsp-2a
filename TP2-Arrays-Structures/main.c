#include <stdio.h>
#include <string.h>
#include "sort.h"
#include "grid.h"
#include "plot.h"


void printArray(float* array, size_t size) {
	putchar('{');
	
	for (int i = 0; i < size; i++) {
		printf("%f, ", array[i]);
	}
	
	puts("\b\b}");
}

int main() {
//	float array[] = {7, 5, 3, 11, -1};
//	size_t size = sizeof(array) / sizeof(array[0]);
//	float sortedArray[size];
//	memset(sortedArray, 0, size);
//	
//	printArray(array, size);
//	printArray(sortedArray, size);
//	sort(array, sortedArray, size);
//	printArray(sortedArray, size);
	
	Grid* grid = newGrid(32, 16, '*');
	printGrid(grid);
	printf("\n");
	
//	plotVerticalLine(grid, 1, 2.0f, 3.0f, '|');
//	plotVerticalLine(grid, 2, 1.7f, 3.3f, '|');
//	plotVerticalLine(grid, 3, 1.2f, 3.8f, '|');
//	plotVerticalLine(grid, 7, 0.5f, 1.5f, '|');
//	printGrid(grid);
	
	Point pointsArray[] = {{2, 2}, {2, 10}, {8, 30},
							{14, 10}, {14, 2}, {8, 18}};
	plotPolygon(grid, pointsArray, 6, '|');
	
	freeGrid(grid);
	return 0;
}
