//
// Created by pauldance on 25/01/2020.
//
#include <glob.h>


#ifndef TP2_ARRAYS_STRUCTURES_SORT_H
#define TP2_ARRAYS_STRUCTURES_SORT_H

size_t getInsertIndex(const float* array, size_t maxIndex, float value);
void insertValueAt(float* array, size_t index, size_t maxIndex, float value);
void insertValue(float* array, size_t maxIndex, float value);
void sort(float* array, float* resultBuffer, size_t size);

#endif //TP2_ARRAYS_STRUCTURES_SORT_H
