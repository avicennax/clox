#include "mintest.h"
#include "chunk.h"

 int tests_run = 0;

static char* test_chunk() {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, constant, 123);

  mu_assert("error, chunk.capacity != 8", chunk.capacity == 8);
  return 0;
}

static char* all_tests() {
  mu_run_test(test_chunk);
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