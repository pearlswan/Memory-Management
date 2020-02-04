#include <inttypes.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"
#define DEFAULT_SIZE 4096

// Search for a free block that at least have
// size
BlockHeader* searchFreelist(uintptr_t size) {
BlockHeader* curr = FreelistHead;
while (curr != NULL) {
	if (curr->size >= size) {
		return(curr);
	}
	curr = curr->next;
}
return NULL;
}

// Insert a block to the free list
void insertBlock(BlockHeader* block) {
if (FreelistHead == NULL) {
	FreelistHead = block;
} else {
	freemem(POINTER_ADD(block, HEADER_SIZE));
}
}

// delete a free block in the free list
void deleteBlock(BlockHeader* block) {
if ((uintptr_t)block == (uintptr_t)FreelistHead) {
	FreelistHead = FreelistHead->next;
	return;
}
BlockHeader* curr = FreelistHead;
while ((uintptr_t)curr->next != (uintptr_t)block) {
	curr = curr->next;
}
if (curr->next->next == NULL) {
	curr->next = NULL;
	return;
}
block->next = NULL;
curr->next = curr->next->next;
}

void* getmem(uintptr_t size) {
check_heap();
*total_size += size;
uintptr_t resize;  // Adjusted size
BlockHeader* newBlock;  // A temp block
BlockHeader* curr;
if (size + HEADER_SIZE < SMALLEST_BLOCK) {
	resize = SMALLEST_BLOCK;
} else if (size % ALIGNMENT != 0) {
	resize = (size / ALIGNMENT + 1) * ALIGNMENT + HEADER_SIZE;
} else {
	resize = size + HEADER_SIZE;
}
curr = searchFreelist(resize);
// Case when didn't find appropriate block,
// get a new block
if (curr == NULL) {
	if (resize > DEFAULT_SIZE) {
		newBlock = (BlockHeader*) malloc(resize);
		newBlock->size = resize;
	} else {
		newBlock = (BlockHeader*) malloc(DEFAULT_SIZE);
		newBlock->size = DEFAULT_SIZE;
	}
        newBlock->next = NULL;
	insertBlock(newBlock);
	curr = searchFreelist(resize);
}
// Case when need to split
if (curr->size - resize >= SMALLEST_BLOCK) {
	newBlock = POINTER_ADD(curr, (curr->size - resize));
	newBlock->size = resize;
	curr->size = curr->size - resize;
	newBlock->next = NULL;
	return(POINTER_ADD(newBlock, HEADER_SIZE));
} else {
	deleteBlock(curr);
	return(POINTER_ADD(curr, HEADER_SIZE));
}
}
