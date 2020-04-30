#include <stdio.h>
#include <stdlib.h>


char* intToBits(long long n, char* buffer) {
    short length = 8 * sizeof(n);
    long long mask = 1LL;
    buffer[length] = 0;

    for (short i = length - 1; i >= 0; i--) {
        buffer[i] = 1 - ((n & mask) == 0) + 48;
        mask <<= 1;
    }

    return buffer;
}


int main(int argc, char** argv) {
    char bits[8 * sizeof(long long) + 1];
    printf("%s\n", intToBits(strtoll(argv[1], NULL, 0), bits));
}
