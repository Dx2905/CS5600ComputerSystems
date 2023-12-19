#ifndef PM_HEAP_H
#define PM_HEAP_H

#include <stdint.h>
#include <stddef.h>
#define PM_HEAP_SIZE (9 * 4 * 1024) // 10MB
#define PM_PAGE_SIZE 4096 // 4KB
#define DISK_STORE "disk_store.bin"

void* pm_malloc(size_t size);
void pm_free(void* ptr);
void pm_init();
void print(int i);
//static int random_page();
void* pm_access(void* ptr);
void pm_cleanup();
#endif

