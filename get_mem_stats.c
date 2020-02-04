// gets all statistics
// Author: Yangming Ke

#include "mem_impl.h"
#include <stdio.h>
#include <stdlib.h>

void get_mem_stats(uintptr_t* total_size,
		uintptr_t* total_free, uintptr_t* n_free_blocks) {
  BlockHeader* cur =  FreelistHead;
  *total_free = 0;
  *n_free_blocks = 0;
  while (cur != NULL) {
    *total_free += cur->size;
    *n_free_blocks += 1;
    cur = cur->next;
  }
}
