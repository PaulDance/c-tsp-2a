#include <stdio.h>
#include <stdlib.h>


void printArray(int array[], size_t size) {
	printf("{");
	
	for (size_t i = 0; i < size - 1; i++) {
		printf("%i, ", array[i]);
	}
	
	printf("%i}\n", array[size - 1]);
}

void squares(int array[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		array[i] *= array[i];
	}
}

int main() {
	int array1[] = {1, 2, 3, 4};
	printArray(array1, 4);
	squares(array1, 4);
	printArray(array1, 4);
	
	int* array2 = malloc(4 * sizeof(int));
	printf("array2 = %p: ", array2);
	printArray(array2, 4);
	free(array2);
	
	return 0;
}
