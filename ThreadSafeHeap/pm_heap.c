#include <stddef.h>
#include <pthread.h>

#define PM_HEAP_SIZE (10 * 1024 * 1024) // 10MB
#define PM_BLOCK_HEADER_SIZE sizeof(struct pm_block)

// Block of memory with header information
struct pm_block {
    size_t size;           // Size of the block
    struct pm_block* next; // Pointer to the next block
    char data[];           // Start of this block
};

// Heap memory and free list
static char pm_heap[PM_HEAP_SIZE];
static struct pm_block* free_list;

// Mutex for thread safety
static pthread_mutex_t pm_mutex = PTHREAD_MUTEX_INITIALIZER;

void pm_heap_init() {
    struct pm_block* free_block = (struct pm_block*) pm_heap;
    free_block->size = PM_HEAP_SIZE - PM_BLOCK_HEADER_SIZE;
    free_block->next = NULL;
    free_list = free_block;
}

void* pm_malloc(size_t size) {
    pthread_mutex_lock(&pm_mutex);
    
    // Search the free list for a block of the appropriate size
    struct pm_block* prev = NULL;
    struct pm_block* current = free_list;
    while (current != NULL) {
        if (current->size >= size) {
            // Found a free block that can be used
            if (current->size >= size + PM_BLOCK_HEADER_SIZE) {
                // Split the block into a used block and a free block
                struct pm_block* new_free_block = (struct pm_block*) (current->data + size);
                new_free_block->size = current->size - size - PM_BLOCK_HEADER_SIZE;
                new_free_block->next = current->next;
                current->size = size;
                current->next = NULL;
                if (prev == NULL) {
                    free_list = new_free_block;
                } else {
                    prev->next = new_free_block;
                }
            } else {
                // Use the entire free block
                if (prev == NULL) {
                    free_list = current->next;
                } else {
                    prev->next = current->next;
                }
            }
            pthread_mutex_unlock(&pm_mutex);
            return current->data;
        }
        prev = current;
        current = current->next;
    }
    
    // No free block found
    pthread_mutex_unlock(&pm_mutex);
    return NULL;
}

void pm_free(void* ptr) {
    pthread_mutex_lock(&pm_mutex);
    
    // Find the block to free
    struct pm_block* current = (struct pm_block*) ((char*) ptr - PM_BLOCK_HEADER_SIZE);
    
    // Find the location to insert the free block in the free list
    struct pm_block* prev = NULL;
    struct pm_block* next = free_list;
    while (next != NULL && next < current) {
        prev = next;
        next = next->next;
    }
    
    // Insert the free block into the free list
    if (prev == NULL) {
        free_list = current;
    } else {
        prev->next = current;
    }
    current->next = next;
    
    pthread_mutex_unlock(&pm_mutex);
}

