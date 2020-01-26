#include <stdio.h>
#include "memory_alloc.h"


/**
 * Initialize the memory allocator
 */
void initMemory() {
	/* TODO */
}

/**
 * Return the number of consecutive blocks starting from first.
 */
int nbOfConsecutiveBlocks(int first) {
	/* TODO */
	return -1;
}

/* Reorder memory blocks */
void reorderMemory() {
	/* TODO (exercise 2) */
}

/**
 * Allocate size consecutive bytes and return the index of the first
 * memory block.
 */
int allocateMemory(size_t size) {
	/* TODO */
	return -1;
}

/**
 * Free the size bytes memory space starting at address addr.
 */
void freeMemory(int addr, size_t size) {
	/* TODO */
}

/**
 * Print the current status of the memory allocator.
 */
void printMemory() {
	printf("---------------------------------\n");
	printf("\tBlock size: %lu\n", sizeof(memory.blocks[0]));
	printf("\tAvailable blocks: %lu\n", memory.availableBlocks);
	printf("\tFirst free: %d\n", memory.firstBlock);
	printf("\tStatus: ");
	printMemoryError(memory.lastErrorNumber);
	printf("\tContent:  ");
	
	/* TODO: browse the available blocks and print their index. */
	
	printf("\n---------------------------------\n");
}


/**
 * Print a message corresponding to the given error number.
 */
void printMemoryError(MemoryErrorNumber errorNumber) {
	switch (errorNumber) {
		case SUCCESS_SIGNAL:
			printf("Success.\n");
			break;
		case NO_MEMORY_ERROR:
			printf("Not enough memory.\n");
			break;
		case SHOULD_PACK_ERROR:
			printf("Not enough contiguous blocks.\n");
			break;
		default:
			break;
	}
}


