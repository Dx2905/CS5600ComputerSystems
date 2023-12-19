#include "pm_heap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  bool valid;
  bool on_disk;
  char disk_file[256];
  size_t disk_offset;
    size_t disk_id;
} page_entry_t;

static char phys_mem[PM_HEAP_SIZE];
static page_entry_t page_table[PM_HEAP_SIZE / PM_PAGE_SIZE];
static size_t fifo_queue[PM_HEAP_SIZE / PM_PAGE_SIZE];
static size_t fifo_front = 0, fifo_back = 0;

void pm_init() {
  srand(time(NULL));
}

// void print(int i){

//   printf(" page %d data: %d\n", i, *(int*)(phys_mem + i * PM_PAGE_SIZE));

// }
void print(int i) {
  int* value_ptr = (int*)(phys_mem + i * PM_PAGE_SIZE);
  printf("Page %d data: %d\n", i, *value_ptr);
}

void pm_cleanup() {
  // Nothing to do here
}

void enqueue(size_t page_idx) {
  fifo_queue[fifo_back] = page_idx;
  fifo_back = (fifo_back + 1) % (PM_HEAP_SIZE / PM_PAGE_SIZE);
}

size_t dequeue() {
  size_t page_idx = fifo_queue[fifo_front];
  fifo_front = (fifo_front + 1) % (PM_HEAP_SIZE / PM_PAGE_SIZE);
  return page_idx;
}
void* pm_malloc(size_t size) {
    size_t num_pages = (size + PM_PAGE_SIZE - 1) / PM_PAGE_SIZE;

    for (size_t i = 0; i < PM_HEAP_SIZE / PM_PAGE_SIZE; ++i) {
        if (!page_table[i].valid) {
            size_t j;
            for (j = 0; j < num_pages; ++j) {
                if (page_table[i + j].valid) {
                    break;
                }
            }
            if (j == num_pages) {
                for (j = 0; j < num_pages; ++j) {
                    page_table[i + j].valid = true;
                }
                size_t* p = (size_t*)(phys_mem + i * PM_PAGE_SIZE);
                *p = num_pages;
                
                enqueue(i);
                return p + 1;
            }
            i += j;
        }
    }
size_t page_to_replace = dequeue();
    enqueue(page_to_replace);

    // Print the data of the replaced page
    printf("page_to_replace: %zu\n", page_to_replace);
    printf("Replaced page %zu data before writing to disk: %lu\n", page_to_replace, *(int*)phys_mem + page_to_replace * PM_PAGE_SIZE);
    
    // Write the replaced page data back to disk before eviction
    char file_name[20];
    page_table[page_to_replace].disk_id = rand() % 100;
    // page_table[page_to_replace].disk_id = page_to_replace;
    sprintf(file_name, "page_%zu.txt", page_table[page_to_replace].disk_id);
    // sprintf(file_name, "page_%zu.txt", page_to_replace);
    FILE* disk_file = fopen(file_name, "w");
    if (!disk_file) {
        perror("Error opening disk store file");
        exit(EXIT_FAILURE);
    }
    fwrite(phys_mem + page_to_replace * PM_PAGE_SIZE, PM_PAGE_SIZE , 1, disk_file);
    // fprintf(disk_file, "%s", phys_mem + page_to_replace * PM_PAGE_SIZE);

    // fprintf(disk_file, "%lu", *(int*)phys_mem + page_to_replace * PM_PAGE_SIZE);
    fclose(disk_file);
    sprintf(file_name, "page_%zu.txt", page_table[page_to_replace].disk_id);
    disk_file = fopen(file_name, "r");
    char buffer[PM_PAGE_SIZE];
    fread(buffer, PM_PAGE_SIZE, 1, disk_file);
    fclose(disk_file);
    // sprintf(file_name, "page_%zu.txt", page_to_replace);
    // disk_file = fopen(file_name, "r");
    // char buffer[PM_PAGE_SIZE];
    // fread(buffer, PM_PAGE_SIZE, 1, disk_file);
    // fclose(disk_file);

    printf("Contents of disk file: %d\n", *(int*)buffer);
    page_table[page_to_replace].on_disk = true;
    page_table[page_to_replace].valid = false;
    page_table[page_to_replace].disk_offset = 0;

    // Assign a new disk ID to the evicted page
    // page_table[page_to_replace].disk_id = rand() % 100;
    // page_table[page_to_replace].disk_id = page_to_replace;

    printf("Replaced page %zu data after reading from disk: %lu\n", page_to_replace, *(int*)phys_mem + page_to_replace * PM_PAGE_SIZE);

    // Allocate memory after replacing pages
    for (size_t i = 0; i < PM_HEAP_SIZE / PM_PAGE_SIZE; ++i) {
        if (!page_table[i].valid) {
          size_t j;
          for (j = 0; j < num_pages; ++j) {
            if (page_table[i + j].valid) {
              break;
            }
          }
          if (j == num_pages) {
            for (j = 0; j < num_pages; ++j) {
              page_table[i + j].valid = true;
            }
            size_t* p = (size_t*)(phys_mem + i * PM_PAGE_SIZE);
            *p = num_pages;
            return p + 1;
          }
          i += j;
        }
      }

      // This point should never be reached
      fprintf(stderr, "Error: Failed to allocate memory\n");
      exit(EXIT_FAILURE);
}
void pm_free(void* ptr) {
  size_t* p = (size_t*)ptr - 1;
  size_t index = ((char*)p - phys_mem) / PM_PAGE_SIZE;
  size_t num_pages = *p;

  // Mark the pages as invalid
  for (size_t i = 0; i < num_pages; ++i) {
    page_table[index + i].valid = false;
    page_table[index + i].on_disk = false;
    page_table[index + i].disk_offset = 0;
  }
}
void* pm_access(void* ptr) {
  size_t* p = (size_t*)ptr - 1;
  size_t offset = (char*)p - phys_mem;
  size_t page_idx = offset / PM_PAGE_SIZE;
  size_t num_pages = *p;
  // for (size_t i = 0; i < num_pages; ++i) {
    // size_t current_page_idx = page_idx + i;
    size_t current_page_idx = page_idx;
    if (page_table[current_page_idx].on_disk) {
      // Find a free page in the physical memory to load the data from disk
      size_t free_page_idx = dequeue();
      enqueue(free_page_idx);

      // Write the replaced page's data back to disk
      char disk_file_name[32];
      // sprintf(disk_file_name, "page_%zu.txt", page_table[current_page_idx].disk_id);
      sprintf(disk_file_name, "page_%zu.txt", page_table[free_page_idx].disk_id);
      FILE* disk_file = fopen(disk_file_name, "w");
      size_t disk_offset_to_replace = page_table[free_page_idx].disk_offset;
      fseek(disk_file, disk_offset_to_replace, SEEK_SET);
      fwrite(phys_mem + free_page_idx * PM_PAGE_SIZE, PM_PAGE_SIZE, 1, disk_file);
      fclose(disk_file);

      // Update the status of the replaced page
      page_table[free_page_idx].valid = false;
      page_table[free_page_idx].on_disk = true;
      // page_table[free_page_idx].disk_id = page_table[current_page_idx].disk_id;

      // Read the data from the disk into the newly allocated page
      sprintf(disk_file_name, "page_%zu.txt", page_table[current_page_idx].disk_id);
      FILE* disk_file1 = fopen(disk_file_name, "r");
      size_t disk_offset = page_table[current_page_idx].disk_offset;
      fseek(disk_file1, disk_offset, SEEK_SET);
      fread(phys_mem + free_page_idx * PM_PAGE_SIZE, PM_PAGE_SIZE, 1, disk_file1);
      fclose(disk_file1);

      // Update the status of the pages
      page_table[free_page_idx].valid = true;
      page_table[current_page_idx].on_disk = false;

      // Update the page_table entry for the new location of the page in the physical memory
      page_table[free_page_idx].disk_offset = disk_offset;

      // Swap the page table entries
      page_entry_t tmp_entry = page_table[free_page_idx];
      page_table[free_page_idx] = page_table[current_page_idx];
      page_table[free_page_idx].disk_offset = tmp_entry.disk_offset; // Update disk_offset for new location
      page_table[current_page_idx] = tmp_entry;
    }
 return (void*)((char*)phys_mem + (offset % PM_PAGE_SIZE) + page_idx * PM_PAGE_SIZE);
}
