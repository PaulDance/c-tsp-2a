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

void initArray(int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = 0;
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

    initArray(array2, 4);
    printArray(array2, 4);

    initArray(array1, 4);
    printArray(array1, 4);

    printf("array1 = %p,\t&array1 = %p\n", array1, &array1);
    printf("array2 = %p,\t\t\t&array2 = %p\n", array2, &array2);

    printf("sizeof(array1) = %lu,\tsizeof(&array1) = %lu,\tsizeof(*&array1) = %lu\n",
           sizeof(array1), sizeof(&array1), sizeof(*&array1));
    printf("sizeof(array2) = %lu,\t\tsizeof(&array2) = %lu,\tsizeof(*&array2) = %lu\n",
           sizeof(array2), sizeof(&array2), sizeof(*&array2));

    free(array2);
    return 0;
}
