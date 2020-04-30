#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"


void modify(FILE* file, const char* studentName, const u_int8_t newGrade) {
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    size_t nbOfStudents = fileSize / sizeof(Student);
    Student* students = (Student*) malloc(fileSize);
    fread(students, sizeof(Student), nbOfStudents, file);

    for (size_t i = 0UL; i < nbOfStudents; i++) {
        if (strcmp(studentName, students[i].name) == 0) {
            students[i].grade = newGrade;
            fseek(file, i * sizeof(Student), SEEK_SET);
            fwrite(&students[i], sizeof(Student), 1UL, file);
            break;
        }
    }

    for (size_t i = 0UL; i < nbOfStudents; i++) {
        printf("%s: %i\n", students[i].name, students[i].grade);
    }
}


int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <student-name> <new-grade>\n"
                        "\tfile: The file to read students names and grades from.\n"
                        "\tstudent-name: The student name to modify the grade for.\n"
                        "\tnew-grade: The new grade to give to the student. Must be included between 0 and 100.\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const u_int8_t newGrade = strtoul(argv[3], NULL, 0);
    char* studentName = argv[2];
    FILE* file = fopen(argv[1], "r+");

    if (newGrade > 100) {
        fprintf(stderr, "Grade should be an integer included between 0 and 255.\n");
        return EXIT_FAILURE;
    }

    if (file == NULL) {
        fprintf(stderr, "Error when opening file.\n");
        return EXIT_FAILURE;
    }

    modify(file, studentName, newGrade);
    return EXIT_SUCCESS;
}
