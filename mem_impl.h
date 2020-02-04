// Declaration of a BlockHeader struct
// Author: Yicheng Wang
#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <inttypes.h>
#define HEADER_SIZE 16
#define ALIGNMENT 16
#define SMALLEST_BLOCK 32
#define POINTER_ADD(p, x) ((void*)((char*)(p) + (x)))
#define POINTER_SUB(p, x) ((void*)((char*)(p) - (x)))

typedef struct Header {
uintptr_t size;  // Size of the free block

struct Header* next;  // Pointer to the next free block
} BlockHeader;

BlockHeader* FreelistHead;

uintptr_t* total_size;

uintptr_t* total_free;

uintptr_t* n_free_blocks;

#endif
