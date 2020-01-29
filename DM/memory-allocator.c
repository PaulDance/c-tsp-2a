#include <stdio.h>
#include <stdbool.h>
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
	unsigned int count = 1;
	
	while (i != NULL_BLOCK) {
		if (memory.blocks[i] == i + 1) {
			count++;
		}
		else {
			return count;
		}
		
		i = memory.blocks[i];
	}
	
	return count;
}

unsigned int swapBlocksRight(unsigned int leftIndex, unsigned int middleIndex) {
	unsigned int tmp = memory.blocks[middleIndex];
	memory.blocks[middleIndex] = memory.blocks[tmp];
	memory.blocks[tmp] = middleIndex;
	
	if (leftIndex != NULL_BLOCK) {
		memory.blocks[leftIndex] = tmp;
	}
	
	if (middleIndex == memory.firstBlock) {
		memory.firstBlock = tmp;
	}
	
	return tmp;
}

/* Reorder memory blocks */
void reorderMemory() {
	unsigned int i, iterNb, lastIndex, iterLimit = memory.availableBlocks - 1;
	bool swapped;
	
	do {
		swapped = false;
		i = memory.firstBlock;
		iterNb = 0;
		lastIndex = NULL_BLOCK;
		
		while (iterNb < iterLimit) {
			if (i > memory.blocks[i]) {
				lastIndex = swapBlocksRight(lastIndex, i);
				swapped = true;
			}
			else {
				lastIndex = i;
				i = memory.blocks[i];
			}
			
			iterNb++;
		}
		
		iterLimit--;
	} while (swapped);
	
	memory.lastErrorNumber = SUCCESS_SIGNAL;
}

unsigned int sizeToBlocks(size_t size) {
	return size / sizeof(memory_page_t) + (size % sizeof(memory_page_t) != 0);
}

/**
 * Allocate size consecutive bytes and return the index of the first
 * memory block.
 */
int allocateMemory(size_t size) {
	unsigned int sizeInBlocks = sizeToBlocks(size);
	
	if (sizeInBlocks > memory.availableBlocks) {
		memory.lastErrorNumber = NO_MEMORY_ERROR;
		return -1;
	}
	else {
		if (memory.lastErrorNumber == SHOULD_PACK_ERROR) {
			reorderMemory();
		}
		
		unsigned int count, lastAvailableBlock = memory.firstBlock, i = lastAvailableBlock;
		
		while (i != NULL_BLOCK) {
			count = nbOfConsecutiveBlocks(i);
			
			if (count < sizeInBlocks) {
				lastAvailableBlock = i + count - 1;
				i = memory.blocks[lastAvailableBlock];
			}
			else {
				if (i == memory.firstBlock) {
					memory.firstBlock = memory.blocks[i + sizeInBlocks - 1];
				}
				else {
					memory.blocks[lastAvailableBlock] = memory.blocks[i + sizeInBlocks - 1];
				}
				
				memory.availableBlocks -= sizeInBlocks;
				memory.lastErrorNumber = SUCCESS_SIGNAL;
				return i;
			}
		}
		
		memory.lastErrorNumber = SHOULD_PACK_ERROR;
		return -1;
	}
}

/**
 * Free the size bytes memory space starting at address addr.
 */
void freeMemory(unsigned int addr, size_t size) {
	unsigned int sizeInBlocks = sizeToBlocks(size);
	
	for (unsigned int i = addr; i < addr + sizeInBlocks - 1; i++) {			// The free function cannot be in O(1) because the linked
		memory.blocks[i] = i + 1;											// list has to be written again, so it is in O(sizeInBlocks).
	}
	
	memory.blocks[addr + sizeInBlocks - 1] = memory.firstBlock;
	memory.firstBlock = addr;
	memory.availableBlocks += sizeInBlocks;
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


