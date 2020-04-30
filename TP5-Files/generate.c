#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void generate(FILE* inFile, FILE* outFile, u_int8_t initialGrade) {
    char readName[STUDENT_NAME_MAX_LENGTH];

    while (fgets(readName, STUDENT_NAME_MAX_LENGTH, inFile)) {
        Student student;
        student.grade = initialGrade;
        strcpy(student.name, readName);
        student.name[strlen(student.name) - 1] = '\0';
        fwrite(&student, sizeof(Student), 1, outFile);
    }
}


int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <in-file> <out-file> <initial-grade>\n"
                        "\tin-file: The file to read students names from.\n"
                        "\tout-file: The file written to receive the student names and initial grades.\n"
                        "\tinitial-grade: The initial grade to give to each student. Must be included between 0 and 100.\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const u_int8_t initialGrade = strtoul(argv[3], NULL, 0);
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = fopen(argv[2], "w");

    if (initialGrade > 100) {
        fprintf(stderr, "Grade should be an integer included between 0 and 255.\n");
        return EXIT_FAILURE;
    }

    if (inFile == NULL) {
        fprintf(stderr, "Error when opening input file.\n");
        return EXIT_FAILURE;
    }

    if (outFile == NULL) {
        fprintf(stderr, "Error when opening output file.\n");
        return EXIT_FAILURE;
    }

    generate(inFile, outFile, initialGrade);
    return EXIT_SUCCESS;
}
