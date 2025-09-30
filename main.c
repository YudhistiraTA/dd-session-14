#include <stdint.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "arena.h"
#include "display.h"
#include "list.h"
#include "terminal.c"

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
  history->current_index++;

  return 0;
}

int main() {
  // Arena allocator with 1MB size
  Arena* arena = arena_new(1024 * 1024);
  if (!arena) return -1;

  // Initialize history
  History* history = (History*)arena_alloc(arena, sizeof(History));
  if (!history) return -1;
  history->oldest = NULL;
  history->newest = NULL;
  history->current = NULL;

  // Start at position (0,0)
  push(arena, history, 0, 0);

  // Set terminal to unbuffered input mode
  set_unbuffered_input();

  // Main loop
  char command = ' ';
  do {
    render(history, command);
    switch (command = getchar()) {
      case 'w':
        if (history->current->y > 0) {
          push(arena, history, history->current->x, history->current->y - 1);
        }
        break;
      case 's':
        if (history->current->y < 9) {
          push(arena, history, history->current->x, history->current->y + 1);
        }
        break;
      case 'a':
        if (history->current->x > 0) {
          push(arena, history, history->current->x - 1, history->current->y);
        }
        break;
      case 'd':
        if (history->current->x < 9) {
          push(arena, history, history->current->x + 1, history->current->y);
        }
        break;
      case 'z':  // Undo
        if (history->current->prev != NULL) {
          history->current = history->current->prev;
          history->current_index--;
        }
        break;
      case 'x':  // Redo
        if (history->current->next != NULL) {
          history->current = history->current->next;
          history->current_index++;
        }
        break;
      case 'q':
        break;
      default:
        printf("Invalid command!\n");
    }
  } while (command != 'q');

  // Clean up
  restore_terminal();
  arena_free(arena);
  return 0;
}