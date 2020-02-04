// Interface header file for project Memory Manager.
// Group member: Yangming Ke  Yicheng Wang
// Author of mem.h: Yicheng Wang

#ifndef MEM_H
#define MEM_H

#include <inttypes.h>
#include <stdio.h>
// st size bytes of memory
void* getmem(uintptr_t size);

// Return the block of storage at location p
// to the pool of available free storage
void freemem(void* p);

// Store statistics about the current state of the memory manager
// in the three integer variables whose addresses are given as arguments
void get_mem_stats(uintptr_t* total_size,
	uintptr_t* total_free, uintptr_t* n_free_blocks);

// Print a formatted listing to file f showing the blocks on the free list.
void print_heap(FILE* f);

// Check for possible problems with the free list data structure
void check_heap();

#endif
