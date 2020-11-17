#include <stdio.h>
#include <stdbool.h>
#include "memory-allocator.h"


/**
 * Initializes the memory allocator.
 */
void initMemory() {
    // Initial size and first block;
    memory.availableBlocks = DEFAULT_SIZE;
    memory.firstBlock = 0;

    // write the sequential linked list,
    for (unsigned int i = memory.firstBlock; i < memory.availableBlocks - 1; i++) {
        memory.blocks[i] = i + 1;
    }

    // connect the last block to nothing and signal a success.
    memory.blocks[memory.availableBlocks - 1] = NULL_BLOCK;
    memory.lastErrorNumber = SUCCESS_SIGNAL;
}

/**
 * Returns the number of consecutive blocks starting from
 * the given memory block index first. It counts one section
 * of consecutive blocks that follow after first, the result
 * is thus always greater than or equals to 1.
 * 
 * @param first The memory block index to start counting from.
 * @return The number of consecutive blocks from first.
 */
unsigned int nbOfConsecutiveBlocks(unsigned int first) {
    unsigned int i = first;
    unsigned int count = 1;

    while (i != NULL_BLOCK) {
        if (memory.blocks[i] == i + 1) {
            count++;
        } else {
            return count;
        }

        i = memory.blocks[i];
    }

    return count;
}

/**
 * Swaps two linked blocks of the memory from left to right.
 * 
 * @param leftIndex The index of the previous block, i.e. the
 *					parent of the middleIndex in the linked
 *					list that is the memory. If there is no
 *					such parent because middleIndex is the first
 *					block of the memory, then it is ignored.
 * @param middleIndex The index of the block to push to the
 *					right of the memory.
 * @return The next left index.
 */
unsigned int swapBlocksRight(unsigned int leftIndex, unsigned int middleIndex) {
    // Saving the index on the right,
    // the middle block is connected to its right,
    // and the right block to the middle one;
    unsigned int rightIndex = memory.blocks[middleIndex];
    memory.blocks[middleIndex] = memory.blocks[rightIndex];
    memory.blocks[rightIndex] = middleIndex;

    // If the given block has no parent,
    if (middleIndex == memory.firstBlock) {
        // then make the new middle block the new first,
        memory.firstBlock = rightIndex;
    } else {
        // otherwise, the left block is connected to the new middle;
        memory.blocks[leftIndex] = rightIndex;
    }

    // finally the next left index is the new middle.
    return rightIndex;
}

/**
 * Reorders memory blocks by applying a bubble sort.
 */
void reorderMemory() {
    unsigned int i, iterNb, leftIndex, iterLimit = memory.availableBlocks - 1;
    // "swapped" optimizes the bubble sort.
    bool swapped = true;

    // While the list is not sorted,
    while (swapped) {
        swapped = false;
        // beginning at the first element,
        i = memory.firstBlock;
        iterNb = 0;
        leftIndex = NULL_BLOCK;

        // a bubble pops up to the limit (last index):
        while (iterNb < iterLimit) {
            // if the current index is greater than its successor,
            if (i > memory.blocks[i]) {
                // then they are swapped,
                leftIndex = swapBlocksRight(leftIndex, i);
                swapped = true;
            } else {
                // otherwise, follow the link to iterate on the next block to make it pop up.
                leftIndex = i;
                i = memory.blocks[i];
            }

            iterNb++;
        }

        iterLimit--;
    }

    // The memory is reordered successfully.
    memory.lastErrorNumber = SUCCESS_SIGNAL;
}

/**
 * Computes the minimum number of blocks required to store
 * a given amount of bytes. It is the ceiling of the division
 * of the given number of bytes and the memory page size.
 * 
 * @example sizeToBlocks(3) == 1 (when sizeof(memory_page_t) == 8)
 * @example sizeToBlocks(8) == 1 (idem)
 * @example sizeToBlocks(9) == 2 (idem)
 * 
 * @param size The number of bytes to allocate or free.
 * @return The conversion in number of blocks.
 */
unsigned int sizeToBlocks(size_t size) {
    return size / sizeof(memory_page_t) + (size % sizeof(memory_page_t) != 0);
}

/**
 * Allocates size consecutive bytes and returns the index of the first
 * memory block.
 * 
 * @param size The number of bytes to allocate.
 * @return The index of the starting point of the memory section if
 * 			successful, -1 otherwise along with an associated memory
 * 			error code.
 */
int allocateMemory(size_t size) {
    unsigned int sizeInBlocks = sizeToBlocks(size);

    // If the user asks for more than is available,
    if (sizeInBlocks > memory.availableBlocks) {
        // return an error directly;
        memory.lastErrorNumber = NO_MEMORY_ERROR;
        return -1;
    } else {
        // if the last allocate terminated on a SHOULD_PACK,
        if (memory.lastErrorNumber == SHOULD_PACK_ERROR) {
            // then sort the memory to free bigger contiguous sections;
            reorderMemory();
        }

        unsigned int count, lastAvailableBlock = memory.firstBlock, i = lastAvailableBlock;

        // while the end of the list is not reached,
        while (i != NULL_BLOCK) {
            count = nbOfConsecutiveBlocks(i);

            // if the count here is not enough,
            if (count < sizeInBlocks) {
                // then get directly to the next free section;
                lastAvailableBlock = i + count - 1;
                i = memory.blocks[lastAvailableBlock];
            } else {
                // otherwise, actually allocate the needed section:
                // if the allocation can be done at the start,
                if (i == memory.firstBlock) {
                    // then make the last block's successor the new first block;
                    memory.firstBlock = memory.blocks[i + sizeInBlocks - 1];
                } else {
                    // otherwise, connect the parent block to jump over the section;
                    memory.blocks[lastAvailableBlock] = memory.blocks[i + sizeInBlocks - 1];
                }

                // finally, decrement the number of available blocks,
                // signal the success of the operation
                // and return the first index of the allocated section;
                memory.availableBlocks -= sizeInBlocks;
                memory.lastErrorNumber = SUCCESS_SIGNAL;
                return i;
            }
        }

        // if no contiguous section big enough was found,
        // signal a SHOULD_PACK and end on an error.
        memory.lastErrorNumber = SHOULD_PACK_ERROR;
        return -1;
    }
}

/**
 * Frees the size bytes memory space starting at address addr.
 */
void freeMemory(unsigned int addr, size_t size) {
    unsigned int sizeInBlocks = sizeToBlocks(size);

    // The free function cannot be in O(1) because the linked
    // list has to be written again, so it is in O(sizeInBlocks).
    for (unsigned int i = addr; i < addr + sizeInBlocks - 1; i++) {
        memory.blocks[i] = i + 1;
    }

    // The end block is connected to the current list head,
    // the beginning block becomes the new list head,
    // and the number of available blocks is incremented.
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
