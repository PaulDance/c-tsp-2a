//
// Created by pauldance on 26/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <setjmp.h>
#include <cmocka.h>
#include "memory-allocator.h"


/**
 * Write something in the buffer.
 */
void useBuffer(int startIndex, size_t size) {
    char* ptr = (char*) &memory.blocks[startIndex];

    for (size_t i = 0; i < size; i++) {
        ptr[i] = 'a' + i;
    }
}

/**
 * Allocate size bytes (or nbPages pages), and free the allocated buffer
 * availableBlocks is the number of available blocks at the beginning.
 */
void testAllocFree(size_t size, int nbPages, int availableBlocks) {
    int res = allocateMemory(size);
    assert_int_equal(memory.lastErrorNumber, SUCCESS_SIGNAL); // allocateMemory should be successful
    assert_int_not_equal(res, -1);           // allocateMemory should return something != -1
    assert_int_equal(memory.availableBlocks,
                     availableBlocks - nbPages); // all the blocks but nbPages should be available
    assert(res >= 0 && res < DEFAULT_SIZE);

    useBuffer(res, size);

    /* free the allocated buffer */
    freeMemory(res, size);
    assert_int_equal(memory.availableBlocks, availableBlocks); // all the blocks should be available
}

/* allocate size bytes */
int testAlloc(size_t size) {
    int res = allocateMemory(size);
    assert_int_equal(memory.lastErrorNumber, SUCCESS_SIGNAL); // allocateMemory should be successful
    assert_int_not_equal(res, -1);           // allocateMemory should return something != -1
    assert_true(res >= 0 && res < DEFAULT_SIZE);

    useBuffer(res, size);
    return res;
}

/* free the buffer located at address addr */
void testMemoryFree(int addr, size_t size) {
    freeMemory(addr, size);
}

void testExo1MemoryInit() {
    /* initialize memory */
    initMemory();
    assert_int_equal(memory.availableBlocks, DEFAULT_SIZE);   // all the blocks should be available
}

void testExo1MemoryPrint() {
    testExo1MemoryInit();
    printMemory();
}

/* allocate size bytes (eg. nbPages blocks) */
void testAllocBlocks(size_t size, int nbPages) {
    testExo1MemoryInit();
    int allocatedBlocks;

    /* allocate a few blocks */
    allocatedBlocks = testAlloc(size); /* allocate 1 byte */
    assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - nbPages);
    assert_in_range(allocatedBlocks, 0, DEFAULT_SIZE);
}

/* allocate 1 byte */
void testExo1AllocOneByte() {
    testAllocBlocks(1, 1);
}

/* allocate 1 page */
void testExo1AllocOnePage() {
    testAllocBlocks(sizeof(memory_page_t), 1);
}

/* allocate 2 pages */
void testExo1AllocTwoPages() {
    testAllocBlocks(2 * sizeof(memory_page_t), 2);
}

/* allocate a few blocks and free them */
void testExo1FreeBlocks() {
    testExo1MemoryInit();
    int allocatedBlocks[DEFAULT_SIZE];

    /* allocate a few blocks */
    allocatedBlocks[0] = testAlloc(1); /* allocate 1 byte */
    assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - 1);

    allocatedBlocks[1] = testAlloc(sizeof(memory_page_t)); /* allocate 1 memory block */
    assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - 2);

    allocatedBlocks[2] = testAlloc(2 * sizeof(memory_page_t)); /* allocate 2 memory blocks */
    assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - 4);

    testMemoryFree(allocatedBlocks[0], 1); /* free 1 byte */

    testMemoryFree(allocatedBlocks[1], sizeof(memory_page_t)); /* free 1 block */

    testMemoryFree(allocatedBlocks[2], 2 * sizeof(memory_page_t)); /* free 2 blocks */
    assert_int_equal(memory.availableBlocks, DEFAULT_SIZE);

    /* allocate a few blocks and free them */
    testAllocFree(1, 1, DEFAULT_SIZE);                       /* allocate 1 byte */
    testAllocFree(sizeof(memory_page_t), 1, DEFAULT_SIZE);   /* allocate 1 memory page */
    testAllocFree(2 * sizeof(memory_page_t), 2, DEFAULT_SIZE); /* allocate 2 memory page */
}

/* allocate multiple blocks and free them */
void testExo1MultipleAlloc() {
    testExo1MemoryInit();
    /* test multiple allocations */
    int allocatedBlocks[DEFAULT_SIZE];

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        allocatedBlocks[i] = testAlloc(1); /* allocate 1 byte */
        assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - (i + 1));
    }
    // the available blocks should be something like:
    // NULL_BLOCK
    // printMemory();

    /* free all the allocated blocks */
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        testMemoryFree(allocatedBlocks[i], 1);
        assert_int_equal(memory.availableBlocks, i + 1);
    }
}

/* test allocation when the system is running out of memory */
void testExo1OutOfMemory() {
    testExo1MemoryInit();
    int allocatedBlocks[DEFAULT_SIZE];

    /* First, use all the memory */
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        allocatedBlocks[i] = testAlloc(1); /* allocate 1 byte */
        // these allocations should succeed
        assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - (i + 1));
    }

    assert_int_equal(memory.availableBlocks, 0); // no more memory

    /* Now, try to allocate one more byte */
    allocatedBlocks[1] = allocateMemory(1);
    assert_int_equal(allocatedBlocks[1], -1); // allocateMemory should return an error
    assert_int_equal(memory.lastErrorNumber,
                     NO_MEMORY_ERROR); // allocateMemory should set lastErrorNumber to NO_MEMORY_ERROR
    assert_int_equal(memory.availableBlocks, 0); // no more memory
}


/* Run a few tests for exercise 2.
 *
 * If you implemented correctly the functions, all these tests should be successfull
 * Of course this test suite may not cover all the tricky cases, and you are free to add
 * your own tests.
 */
void testExo2Reorder() {
    testExo1MemoryInit();
    /* test multiple allocations */
    int allocatedBlocks[DEFAULT_SIZE];

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        allocatedBlocks[i] = testAlloc(1); /* allocate 1 byte */
        assert_int_equal(memory.availableBlocks, DEFAULT_SIZE - (i + 1));
    }

    assert_int_equal(memory.availableBlocks, 0);

    /* free half of the allocated blocks */
    int freedPages = 0;

    for (int i = 0; i < DEFAULT_SIZE; i += 2) {
        testMemoryFree(allocatedBlocks[i], 1);
        freedPages++;
        assert_int_equal(memory.availableBlocks, freedPages);
    }
    // the available blocks should be:
    // [0] -> [2] -> [4] -> [6] -> [8] -> [10] -> [12] -> [14] -> NULL_BLOCK
    //printMemory();

    int res = allocateMemory(sizeof(memory_page_t) * 2);
    // allocation should fail as there's no 2 consecutive blocks
    assert_int_equal(res, -1);
    assert_int_equal(memory.lastErrorNumber, SHOULD_PACK_ERROR);

    // free the remaining allocated blocks
    for (int i = 1; i < DEFAULT_SIZE; i += 2) {
        testMemoryFree(allocatedBlocks[i], 1);
        freedPages++;
        assert_int_equal(memory.availableBlocks, freedPages);
    }
    // the available blocks should be something like:
    // [15] -> [13] -> [11] -> [9] -> [7] -> [5] -> [3] -> [1] -> [0] -> [2] -> [4] -> [6] -> [8] -> [10] -> [12] -> [14] -> NULL_BLOCK
    //printMemory();

    // Now, there are 16 available blocks (but probably randomly distributed)
    // This call should trigger the memory reordering function, and successfully allocate 2 blocks
    res = allocateMemory(sizeof(memory_page_t) * 2);
    assert_int_equal(memory.lastErrorNumber, SUCCESS_SIGNAL);

    // the available blocks should be something like:
    // [2] -> [3] -> [4] -> [5] -> [6] -> [7] -> [8] -> [9] -> [10] -> [11] -> [12] -> [13] -> [14] -> [15] -> NULL_BLOCK
    //printMemory();
}


int main() {
    const struct CMUnitTest tests[] = {
            /*
             * A few tests for exercise 1.
             *
             * If you implemented correctly the functions, all these tests should be successful
             * Of course this test suite may not cover all the tricky cases, and you are free to add
             * your own tests.
             */
            cmocka_unit_test(testExo1MemoryInit),
            cmocka_unit_test(testExo1MemoryPrint),
            cmocka_unit_test(testExo1AllocOneByte),
            cmocka_unit_test(testExo1AllocOnePage),
            cmocka_unit_test(testExo1AllocTwoPages),
            cmocka_unit_test(testExo1FreeBlocks),
            cmocka_unit_test(testExo1MultipleAlloc),
            cmocka_unit_test(testExo1OutOfMemory),

            /*
             * Run a few tests for exercise 2.
             *
             * If you implemented correctly the functions, all these tests should be successful
             * Of course this test suite may not cover all the tricky cases, and you are free to add
             * your own tests.
             */
            cmocka_unit_test(testExo2Reorder)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
