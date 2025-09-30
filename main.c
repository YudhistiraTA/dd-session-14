#include <stdint.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "arena.h"
#include "display.h"
#include "list.h"
#include "terminal.c"

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
        undo(history);
        break;
      case 'x':  // Redo
        redo(history);
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