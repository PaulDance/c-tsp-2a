//
// Created by pauldance on 03/02/2020.
//
#include <stdio.h>


size_t stringLength(const char* string) {
	size_t length = 0UL;
	
	while (string[length] != 0UL) {
		length++;
	}
	
	return length;
}

void stringCopy(char* dest, const char* src, size_t n) {
	for (size_t i = 0UL; i < n && src[i] != '\0'; i++) {
		dest[i] = src[i];
	}
}

void stringConcatenate(char* dest, const char* src, size_t n) {
	const size_t destLength = stringLength(dest);
	
	for (size_t i = 0UL; i < n; i++) {
		dest[destLength + i] = src[i];
	}
	
	dest[destLength + n] = '\0';
}


int main() {
	char src[50], dest[50];
	
	stringCopy(src, "à tous !", 9);
	stringCopy(dest, "Bonjour", 8);
	
	stringConcatenate(dest, src, 9);
	printf("Final destination string: |%s|\n", dest);
	
	return 0;
}
