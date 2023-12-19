#ifndef PM_HEAP_H
#define PM_HEAP_H

#include <stddef.h>

#define PM_HEAP_SIZE (10 * 1024 * 1024) // 10MB
#define PM_BLOCK_HEADER_SIZE sizeof(struct pm_block)

// Block of memory with header information
struct pm_block {
    size_t size;           // Size of the block
    struct pm_block* next; // Pointer to the next block
    char data[];           // Start of this block
};

void pm_heap_init();

void* pm_malloc(size_t size);

void pm_free(void* ptr);

#endif

