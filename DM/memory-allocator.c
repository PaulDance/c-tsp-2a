#include <stdio.h>
#include "memory-allocator.h"


/**
 * Initialize the memory allocator
 */
void initMemory() {
	memory.availableBlocks = DEFAULT_SIZE;
	memory.firstBlock = 0;
	
	for (unsigned int i = memory.firstBlock; i < memory.availableBlocks - 1; i++) {
		memory.blocks[i] = i + 1;
	}
	
	memory.blocks[memory.availableBlocks - 1] = NULL_BLOCK;
	memory.lastErrorNumber = SUCCESS_SIGNAL;
}

/**
 * Return the number of consecutive blocks starting from first.
 */
unsigned int nbOfConsecutiveBlocks(unsigned int first) {
	unsigned int i = first;
	unsigned int consecutiveCount = 0, totalCount = 0;
	
	while (i != NULL_BLOCK) {
		if (memory.blocks[i] == (i + 1)) {
			consecutiveCount += 1;
		}
		else {
			totalCount += consecutiveCount;
			consecutiveCount = 0;
		}
		
		i = memory.blocks[i];
	}
	
	return totalCount;
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
	
	for (unsigned int i = memory.firstBlock; i != NULL_BLOCK; i = memory.blocks[i]) {
		printf("[%i] -> ", i);
	}
	
	puts("NULL_BLOCK");
	printf("---------------------------------\n");
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


