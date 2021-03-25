#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN
} OpCode;

/**
 * uint8_t* is sorta deceptive from my perspective.
 * If actually used, it will actually point to a
 * dynamically sized array in memory, created via 
 * realloc(), whose cells are of size sizeof(uint8_t),
 * which is a byte or 8 bits.
 **/
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

#endif