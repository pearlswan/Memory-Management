// Implementation of the freemem function
// Author: Yicheng Wang

#include "mem_impl.h" 
#include "mem.h"

void freemem(void* p) {

check_heap();
BlockHeader* ptr = POINTER_SUB(p, HEADER_SIZE);  // Points to the Header
BlockHeader* curr = FreelistHead;  // An iterator
// When the freelist is null
if (!curr) {
	FreelistHead = ptr;
	return;
}
// When ptr is before Freelist
if (FreelistHead > ptr) {
	if ((uintptr_t)POINTER_ADD(ptr, ptr->size) >= (uintptr_t)FreelistHead) {
		uintptr_t newSize = ptr->size + FreelistHead->size;
		ptr->next = FreelistHead->next;
		FreelistHead = ptr;
		FreelistHead->size = newSize;
	} else {
		ptr->next = FreelistHead;
		FreelistHead = ptr;
	}
	return;
}
// Looking for the block that is greater than ptr
while (curr->next && curr->next < ptr) {
	curr = curr->next;
}
// When add to the end
if (!curr->next) {
	if ((uintptr_t)POINTER_ADD(curr, curr->size) >= (uintptr_t)ptr) {
		uintptr_t newSize = curr->size + ptr->size;
		curr->size = newSize;
	} else {
		curr->next = ptr;
	}
	return;
}
// When touching on both ends
if (((uintptr_t)POINTER_ADD(curr, curr->size) >= (uintptr_t)ptr) &&
		((uintptr_t)POINTER_ADD(ptr, ptr->size) >= (uintptr_t)curr->next)) {
	uintptr_t newSize = ptr->size + curr->size + curr->next->size;
	curr->size = newSize;
	curr->next = curr->next->next;
// When touching with the preceeding block
} else if ((uintptr_t)POINTER_ADD(curr, curr->size) >= (uintptr_t)ptr) {
	uintptr_t newSize = ptr->size + curr->size;
	curr->size = newSize;
// When touching with the succeeding block
} else if ((uintptr_t)POINTER_ADD(ptr, ptr->size) >= (uintptr_t)curr->next) {
	uintptr_t newSize = ptr->size + curr->next->size;
	ptr->size = newSize;
	ptr->next = curr->next->next;
	curr->next = ptr;
// Put it in the middle
} else {
	ptr->next = curr->next;
	curr->next = ptr;
}
}
