#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NB_ELEMENTS 7


int compare_shorts(const short* i, const short* j) {
	return *i - *j;
}

int compare_doubles(const double* x, const double* y) {
	return round(*x - *y);
}

void print_tab_short(short tab[], size_t nmemb) {
	for (size_t i = 0UL; i < nmemb; i++) {
		printf("tab_short[%lu] = %d\n", i, tab[i]);
	}
}

void print_tab_double(double tab[], size_t nmemb) {
	for (size_t i = 0UL; i < nmemb; i++) {
		printf("tab_double[%lu] = %lf\n", i, tab[i]);
	}
}


int main(){
	short tab_short[NB_ELEMENTS] = {6, 5, 4, 3, 2, 1, 0};
	double tab_double[NB_ELEMENTS] = {7.1, 6.2, 5.3, 4.4, 3.5, 2.6, 1.7};

	printf("tab_short avant tri\n");
	print_tab_short(tab_short, NB_ELEMENTS);
	qsort(tab_short, NB_ELEMENTS, sizeof(short),
		(int (*)(const void*, const void*)) compare_shorts);
	printf("tab_short avant tri\n");
	print_tab_short(tab_short, NB_ELEMENTS);

	printf("tab_double avant tri\n");
	print_tab_double(tab_double, NB_ELEMENTS);
	qsort(tab_double, NB_ELEMENTS, sizeof(double),
		(int (*)(const void*, const void*)) compare_doubles);
	printf("tab_double avant tri\n");
	print_tab_double(tab_double, NB_ELEMENTS);

	return EXIT_SUCCESS;
}
