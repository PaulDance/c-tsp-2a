#include <stdint.h>


#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

/**
 * A block that does not exists.
 */
#define NULL_BLOCK INT32_MAX
/**
 * Default number of blocks.
 */
#define DEFAULT_SIZE 16

/**
 * A memory page is 8 bytes (64 bits).
 */
typedef int64_t memory_page_t;

/**
 * Result of the last memory operation.
 */
typedef enum MemoryErrorNumber {
	/**
	 * Success signal.
	 */
	SUCCESS_SIGNAL,
	/**
	 * Error: not enough memory signal.
	 */
	NO_MEMORY_ERROR,
	/**
	 * Error: not enough consecutive blocks signal.
	 */
	SHOULD_PACK_ERROR,
} MemoryErrorNumber;

typedef struct MemoryAllocator {
	/**
	 * Blocks that can be allocated.
	 */
	memory_page_t blocks[DEFAULT_SIZE];
	/**
	 * Number of available blocks.
	 */
	size_t availableBlocks;
	/**
	 * Index of the first available block.
	 */
	unsigned int firstBlock;
	/**
	 * Error of the last memory operation. to be updated during
	 * each call to freeMemory/memory_alloc/initMemory.
	 */
	MemoryErrorNumber lastErrorNumber;
} MemoryAllocator;

MemoryAllocator memory;

void initMemory();
unsigned int nbOfConsecutiveBlocks(unsigned int first);
void printMemory();
int allocateMemory(size_t size);
void freeMemory(int addr, size_t size);
void printMemoryError(MemoryErrorNumber errorNumber);

#endif    /* MEMORY_ALLOCATOR_H */
