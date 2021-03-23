#include <stdlib.h>

#include "memory.h"

// void pointer has no type - you can cast any pointer
// type to and back from *void.
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  // Either expands / shrinks existing memory block 
  // or unable to do so it allocates a new block
  // and copies the data in the old block to the new 
  // block, then freeing up the old block.
  void* result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
}