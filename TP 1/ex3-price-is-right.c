/*
 * ex3-price-is-right.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Paul Mabileau
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	srand(getpid());
	int correctPrice = rand() % 100;
	int guessedPrice = -1;
	int nbTrialsLeft = 10;
	
	while (nbTrialsLeft != 0) {
		printf("What is your guess?\n");
		scanf("%d", &guessedPrice);
		
		if (guessedPrice == correctPrice) {
			printf("Correct!\n");
			return 0;
		}
		else {
			printf(guessedPrice < correctPrice ? "More...\n" : "Less...\n");
			nbTrialsLeft--;
		}
	}
	
	printf("You lost! Too bad...\n");
}
