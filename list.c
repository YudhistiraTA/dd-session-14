#include "list.h"

int push(Arena* arena, History* history, uint8_t x, uint8_t y) {
  if (history->current != history->newest) {
    // truncate redo history
    history->newest = history->current;
    history->current->next = NULL;
  }

  // define current node
  Node* newNode = (Node*)arena_alloc(arena, sizeof(Node));
  if (!newNode) return -1;
  newNode->x = x;
  newNode->y = y;
  newNode->next = NULL;
  newNode->prev = history->newest;

  // link the previous newest node to the new node
  if (history->newest != NULL) {
    history->newest->next = newNode;
  }

  // update newest and current pointers
  history->newest = newNode;
  history->current = newNode;

  // if the history was empty, set oldest to the new node
  if (history->oldest == NULL) {
    history->oldest = newNode;
  }

  return 0;
}

int undo(History* history) {
  if (history->current->prev != NULL) {
    history->current = history->current->prev;
    return 0;
  }
  return -1;  // No more undo available
}

int redo(History* history) {
  if (history->current->next != NULL) {
    history->current = history->current->next;
    return 0;
  }
  return -1;  // No more redo available
}