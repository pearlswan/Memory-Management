// Implementation of the check_heap function
// Author: Yangming Ke

#include "mem_impl.h"
#include <assert.h>
#include <stdio.h>

// This method checks possible problems in a heap
void check_heap() {
  BlockHeader* prev  = FreelistHead;
  if (FreelistHead != NULL) {
    BlockHeader* curr;
    curr = prev->next;
    while (curr != NULL) {
      // check if memory address is increasing
      assert(prev < curr);
      // check block size
      assert(prev->size > 0 && prev->size >= SMALLEST_BLOCK);
      // check that blocks do not overlap or touch
      assert(prev->size + (uintptr_t) prev != (uintptr_t) curr);
      assert(prev->size + (uintptr_t) prev < (uintptr_t) curr);
      prev = prev->next;
      curr = curr->next;
    }
  }
}
