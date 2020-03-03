#include <stdio.h>
#include <stdlib.h>

void init_tab(int* tab, int size) {
	for(int i = 0; i < size; i++) {
		tab[i] = 5;
	}
}

int main(int argc, char**argv) {
	int size = 12;
	
	if(argc > 1) {
		size = atoi(argv[1]);
	}

	int* buffer = malloc(size * sizeof(int));
	int* value = malloc(sizeof(int));
	*value = 17;
	init_tab(buffer, size);
	printf("value = %d\n", *value);

	for(int i = 0; i < size; i++) {
		printf("buf[%d] = %d\n", i, buffer[i]);
	}
	
	free(buffer);
	free(value);
	return EXIT_SUCCESS;
}
