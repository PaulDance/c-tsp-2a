//
// Created by pauldance on 25/01/2020.
//

#include "sort.h"


/**
 * Computes and returns the index at which a value should be
 * inserted in order to keep the given array sorted between
 * 0 and maxIndex.
 * 
 * @param array The array sorted up to maxIndex.
 * @param maxIndex The maximum element index at which the array
 * 					is sorted.
 * @param value The value to compute the correct position for.
 * @return The insertion index.
 */
int getInsertIndex(float* array, int maxIndex, float value) {
	for (int i = 0; i < maxIndex; i++) {
		if (array[i] > value) {
			return i;
		}
	}
	
	return maxIndex;
}

/**
 * Inserts a given value in the sorted array at the specified
 * position.
 * 
 * @param array The array.
 * @param index The index the value should be inserted at.
 * @param maxIndex The maximum index to consider.
 * @param value The value to insert.
 */
void insertValueAt(float* array, int index, int maxIndex, float value) {
	for (int i = maxIndex; i > index; i--) {
		array[i] = array[i - 1];
	}
	
	array[index] = value;
}

/**
 * Inserts a given value in the partially sorted array at the
 * correct position to maintain ascendant order.
 * 
 * @param array The array sorted up to maxIndex.
 * @param maxIndex The maximum element index at which the array
 * 					is sorted.
 * @param value The value to insert.
 */
void insertValue(float* array, int maxIndex, float value) {
	insertValueAt(array, getInsertIndex(array, maxIndex, value), maxIndex, value);
}

/**
 * Sorts the given array into resultBuffer using insertion sort.
 * 
 * @param array The array to sort.
 * @param resultBuffer The buffer that will contain the sorted
 * 						out version.
 * @param size The size in number of elements of both array and
 * 				resultBuffer.
 */
void sort(float* array, float* resultBuffer, size_t size) {
	for (int i = 0; i < size; i++) {
		insertValue(resultBuffer, i, array[i]);
	}
}
