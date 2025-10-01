#include "display.h"

#include <stdio.h>

void render(History* history, char command) {
  clrscr();
  int seen_field[10][10] = {0};
  Node* temp = history->oldest;
  while (temp != NULL) {
    seen_field[temp->y][temp->x] = 1;
    temp = temp->next;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == history->current->x && i == history->current->y) {
        printf("0 ");
      } else if (seen_field[i][j]) {
        printf("* ");
      } else {
        printf(". ");
      }
    }
    printf("\n");
  }
  printf("Last action: %c\n", command);
  printf("z - undo    x - redo\n");
  printf("w - up      s - down\na - left    d - right\n");
  printf("c - delete\n");
  printf("q - quit\n");
}