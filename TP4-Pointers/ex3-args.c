#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    int sum = 0;

    for (int i = 0; i < argc; i++) {
        printf("argv[%i] @ %p = %s\n", i, &argv[i], argv[i]);
        sum += atoi(argv[i]);
    }

    printf("Sum of arguments = %i\n", sum);
}
