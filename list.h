#ifndef LIST_H
#define LIST_H

#include <stdint.h>

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
  uint8_t current_index;
} History;

#endif  // LIST_H