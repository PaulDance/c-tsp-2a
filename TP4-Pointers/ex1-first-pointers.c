#include <stdio.h>


void squares(int* a, int* b) {
    *a *= *a;
    *b *= *b;
}

int main() {
    int a = 3, b = 4;
    int* aPtr = &a, * bPtr = &b;

    printf("&a\t\t= %p\ta\t\t= %i\n", &a, a);
    printf("&b\t\t= %p\tb\t\t= %i\n", &b, b);
    printf("&aPtr\t= %p\taPtr\t= %p\n", &aPtr, aPtr);
    printf("&bPtr\t= %p\tbPtr\t= %p\n", &bPtr, bPtr);

    squares(aPtr, bPtr);
    puts("");

    printf("&a\t\t= %p\ta\t\t= %i\n", &a, a);
    printf("&b\t\t= %p\tb\t\t= %i\n", &b, b);
    printf("&aPtr\t= %p\taPtr\t= %p\n", &aPtr, aPtr);
    printf("&bPtr\t= %p\tbPtr\t= %p\n", &bPtr, bPtr);

    return 0;
}
