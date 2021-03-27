#include "mintest.h"
#include "memory.h"
#include "chunk.h"

int tests_run = 0;

Chunk getTestChunk() {
  Chunk chunk;
  initChunk(&chunk);
  return chunk;
}

static char* test_writeChunk() {
  Chunk chunk = getTestChunk();
  int constant = addConstant(&chunk, 1.5);
  writeChunk(&chunk, constant, 123);

  mu_assert("error, chunk.capacity != 8", chunk.capacity == 8);
  mu_assert("error, chunk.count != 1", chunk.count == 1);
  // Was confused about why I didn't have to use -> operator to access
  // values[0]. But - I think - values[0] technically returns the value of the 0th
  // memory cell. It's a kind of index based pointer deference.
  mu_assert("error, chunk.constant.values[0] != 1.5", chunk.constants.values[0] == 1.5);

  for (int i = 1; i < 9; i++) {
    constant = addConstant(&chunk, i);
    writeChunk(&chunk, constant, i);
  }
  mu_assert("error, capacity wasn't doubled, chunk.capacity != 8", chunk.capacity == 16);
  mu_assert("error, chunk.count != 9", chunk.count == 9);

  return 0;
}

/**
 * One kinda ass thing about C is you can't really test
 * to see if you've free'd memory - best bet is to assign
 * it to NULL or 0.
 *
 * Obviously sucks for me cause I barely understand the
 * basic shit.
 */
static char* test_freeChunk() {
  Chunk chunk = getTestChunk();
  int constant = addConstant(&chunk, 1.5);
  writeChunk(&chunk, constant, 123);

  freeChunk(&chunk);
  mu_assert("error, chunk count not reset", chunk.code == 0);
  mu_assert("error, chunk capacity not reset", chunk.capacity == 0);
  mu_assert("error, chunk constants not reset", chunk.constants.values == NULL);

  return 0;
}

static char* test_reallocate() {
  uint8_t* dynArrayPointer;
  // Same as:  (type*)reallocate(pointer, sizeof(type) * (oldCount), \
  //  sizeof(type) * (newCount))
  dynArrayPointer = GROW_ARRAY(uint8_t, dynArrayPointer, 0, 1);

  dynArrayPointer[0] = OP_CONSTANT;
  mu_assert("error, DynArrayPointer is NULL", dynArrayPointer != NULL);

  // Same as: reallocate(pointer, sizeof(type) * (oldCount), 0)
  dynArrayPointer = FREE_ARRAY(uint8_t, dynArrayPointer, 1);
  mu_assert("error, DynArrayPointer isn't NULL", dynArrayPointer == NULL);

  return 0;
}

static char* all_tests() {
  mu_run_test(test_writeChunk);
  mu_run_test(test_freeChunk);
  mu_run_test(test_reallocate);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
      printf("%s\n", result);
  }
  else {
      printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}