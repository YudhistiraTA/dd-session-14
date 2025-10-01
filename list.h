#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "arena.h"

typedef struct _Node {
  struct _Node* next;
  struct _Node* prev;
  uint8_t x;
  uint8_t y;
} Node;

typedef struct _History {
  Node* oldest;
  Node* current;
  Node* newest;
} History;

int push(Arena* arena, History* history, uint8_t x, uint8_t y);

int undo(History* history);

int redo(History* history);

int delete(History* history);

#endif  // LIST_H