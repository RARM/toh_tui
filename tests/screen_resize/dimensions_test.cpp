// dimensions_test.cpp
#include <ncurses.h>

inline int get_center(int line) { return line / 2; }

int main(int argc, char const *argv[])
{
    initscr();

    // drawing horizontal line
    for (int i{ 0 }; i < COLS; i++)
        mvprintw(get_center(LINES), i, "-");

    // vertical line
    for (int i{ 0 }; i < LINES; i++)
        mvprintw(i, get_center(COLS), "|");

    mvprintw(LINES/2, COLS/2, "*");

    refresh();

    getch();

    endwin();
    return 0;
}
