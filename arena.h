#ifndef ARENA_H
#define ARENA_H
#include <stdio.h>

typedef struct Arena {
  void* memory;
  size_t offset;
  size_t size;
} Arena;

void* arena_new(size_t size);
void* arena_alloc(Arena* arena, size_t size);
void arena_free(Arena* arena);
#endif  // ARENA_H