#ifndef DISPLAY_H
#define DISPLAY_H
#ifdef _WIN32
#include <conio.h>
#define clrscr() system("cls")
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#include "list.h"

void render(History* history, char command);
#endif  // DISPLAY_H