#include "arena.h"

#include <stdlib.h>

void* arena_new(size_t size) {
  Arena* arena = (Arena*)malloc(sizeof(Arena));
  if (!arena) return NULL;  // Memory allocation failed
  arena->memory = malloc(size);
  if (!arena->memory) {
    free(arena);
    return NULL;  // Memory allocation failed
  }
  arena->offset = 0;
  arena->size = size;
  return arena;
}
void* arena_alloc(Arena* arena, size_t size) {
  if (arena->offset + size > arena->size) {
    return NULL;  // Not enough memory
  }
  void* ptr = (char*)arena->memory + arena->offset;
  arena->offset += size;
  return ptr;
}
void arena_free(Arena* arena) {
  if (arena) {
    free(arena->memory);
    free(arena);
  }
}
