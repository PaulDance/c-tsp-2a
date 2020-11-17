//
// Created by pauldance on 28/02/2020.
//
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc == 2) {
        const int blockSize = 1024;
        char readString[blockSize];
        FILE* file = fopen(argv[1], "r");

        if (file != NULL) {
            while (fgets(readString, blockSize, file)) {
                printf("%s", readString);
            }
        }
    }

    return EXIT_SUCCESS;
}
