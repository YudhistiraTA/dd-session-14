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

// Deletes the history node on current position
int delete(History* history) {
  if (history->current == NULL) {
    return -1;  // No current node to delete
  }

  Node* toDelete = history->current;

  // Update the previous node's next pointer
  if (toDelete->prev != NULL) {
    toDelete->prev->next = toDelete->next;
  } else {
    // If there's no previous node, we're deleting the oldest node
    history->oldest = toDelete->next;
  }

  // Update the next node's prev pointer
  if (toDelete->next != NULL) {
    toDelete->next->prev = toDelete->prev;
  } else {
    // If there's no next node, we're deleting the newest node
    history->newest = toDelete->prev;
  }

  // Move current pointer
  if (toDelete->next != NULL) {
    history->current = toDelete->next;
  } else if (toDelete->prev != NULL) {
    history->current = toDelete->prev;
  } else {
    history->current = NULL;  // List is now empty
  }

  return 0;
}