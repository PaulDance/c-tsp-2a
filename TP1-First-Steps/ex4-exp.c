/*
 * ex4-exp.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Paul Mabileau
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long long factorial(unsigned int n) {
	unsigned long long result = 1ULL;
	
	for (unsigned int i = 2u; i <= n; i++) {
		result *= i;
	}
	
	return result;
}

long double power(long double x, long n) {
	if (n == 0L) {
		return 1.0L;
	}
	else {
		long double result;
		unsigned long exponent;
		
		if (n > 0L) {
			result = x;
			exponent = n;
		}
		else {
			result = 1.0L / x;
			exponent = -n;
		}
		
		for (unsigned long i = 1UL; i < exponent; i++) {
			result *= x;
		}
		
		return result;
	}
}

long double exponential(long double x) {
	long double prevValue = 0, currentValue = 1;
	unsigned int n = 1;
	
	while (fabsl(prevValue - currentValue) > 0.0000001L) {
		prevValue = currentValue;
		currentValue += power(x, n) / factorial(n);
		n++;
	}
	
	return currentValue;
}


int main(int argc, char **argv) {
	printf("%LF\n", exponential(strtold(argv[1], NULL)));
}
