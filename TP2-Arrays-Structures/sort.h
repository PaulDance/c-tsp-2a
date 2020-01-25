//
// Created by pauldance on 25/01/2020.
//
#include <glob.h>


#ifndef TP2_ARRAYS_STRUCTURES_SORT_H
#define TP2_ARRAYS_STRUCTURES_SORT_H

int getInsertIndex(float* array, int maxIndex, float value);
void insertValueAt(float* array, int index, int maxIndex, float value);
void insertValue(float* array, int maxIndex, float value);
void sort(float* array, float* resultBuffer, size_t size);

#endif //TP2_ARRAYS_STRUCTURES_SORT_H
