// screen_size.cpp -- prototype for reading the screen size in a portable way
//
// This program was used to test different methods to calculate the screen size
// in a portable way (compatible with Windows, Linux, and MacOS). Unfortunately,
// the current version of ncurses in MinGW is not allowing to recalculate COLS
// and LINES after it starts. It may be due to the version of ncurses or the
// limitations of the shell.
#include <ncurses.h>

#define VERSION 2

#if VERSION == 2
#include <iostream>

int main(void) {
    int user_input;
    char c;

    std::cout << "Resize your screen and press <enter>." << std::endl;
    c = std::getchar();

    initscr();

    printw("Screen size.\nWidth: %d\nHeight: %d", COLS, LINES);
    refresh();

    timeout(100); // miliseconds
    while ((user_input = getch()) != 'q');

    endwin();
    return 0;
}
#endif

#if VERSION == 1
void reset_values() {
    endwin();
    refresh();
    clear();
}

int main(void) {
    int user_input;

    initscr();

    printw("Screen size.\nWidth: %d\nHeight: %d", COLS, LINES);
    refresh();

    timeout(100); // miliseconds
    while ((user_input = getch()) != 'q') {
        reset_values();
        printw("Screen size.\nWidth: %d\nHeight: %d", COLS, LINES);
        refresh();
    }

    endwin();
    return 0;
}
#endif