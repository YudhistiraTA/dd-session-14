#include <stdio.h>

// For Windows
#ifdef _WIN32
#include <windows.h>

void set_unbuffered_input() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    // Disable line input and echo input modes
    mode &= ~(ENABLE_LINE_INPUT | ECHO_INPUT);
    SetConsoleMode(hStdin, mode);
}

void restore_terminal() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    // Re-enable line input and echo input modes
    mode |= (ENABLE_LINE_INPUT | ECHO_INPUT);
    SetConsoleMode(hStdin, mode);
}

// For Linux/macOS (and WSL)
#else
#include <termios.h>
#include <unistd.h>

void set_unbuffered_input() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void restore_terminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);  // Re-enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
#endif