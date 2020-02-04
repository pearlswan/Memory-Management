// Implementation of the print_heap function
// Author: Yicheng Wang

#include "mem_impl.h"
#include <stdio.h>
#include <stdlib.h>
void print_heap(FILE* f) {
BlockHeader* curr = FreelistHead;
if (f) {
	while (curr) {
		fprintf(f, "%#"PRIxPTR" %#"PRIxPTR"\n", (uintptr_t)POINTER_ADD(curr, HEADER_SIZE), curr->size);
		curr = curr->next;
	}
} else {
	fprintf(stderr, "%s/n", "Wrong output file.");
}
}
