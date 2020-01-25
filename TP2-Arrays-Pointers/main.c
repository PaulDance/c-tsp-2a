#include <stdio.h>
#include <string.h>
#include "sort.h"


void printArray(float* array, size_t size) {
	putchar('{');
	
	for (int i = 0; i < size; i++) {
		printf("%f, ", array[i]);
	}
	
	puts("\b\b}");
}

int main() {
	float array[] = {7, 5, 3, 11, -1};
	size_t size = sizeof(array) / sizeof(array[0]);
	float sortedArray[size];
	memset(sortedArray, 0, size);
	
	printArray(array, size);
	printArray(sortedArray, size);
	sort(array, sortedArray, size);
	printArray(sortedArray, size);
	
	return 0;
}
