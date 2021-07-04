#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
#include "scanner.h"

#define DEBUG(x) fprintf(stderr, x)

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

const char* getTokenName(TokenType type);

#endif