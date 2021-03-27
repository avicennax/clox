#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

#define DEBUG(x) fprintf(stderr, x)

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif