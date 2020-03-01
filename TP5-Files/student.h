//
// Created by pauldance on 28/02/2020.
//

#ifndef TP5_FILES_STUDENT_H
#define TP5_FILES_STUDENT_H

#include <stdlib.h>
#define STUDENT_NAME_MAX_LENGTH 256

typedef struct Student {
	char name[STUDENT_NAME_MAX_LENGTH];
	u_int8_t grade;
} Student;

#endif //TP5_FILES_STUDENT_H
