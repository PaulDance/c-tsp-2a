/*
 * ex2-is-prime.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Paul Mabileau
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool isPrime(long number) {
	for (long i = 2; i < number; i++) {
		if (number % i == 0) {
			return false;
		}
	}
	
	return true;
}


int main(int argc, char **argv) {
	printf("%d\n", isPrime(strtoul(argv[1], NULL, 0)));
}
