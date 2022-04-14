// dim_colors.cpp -- test if colors could be made dim in Windows
#include <ncurses.h>

int main(int argc, char const *argv[])
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    
    for (int i{ 0 }; i < COLS; i++) {
        if (i % 2 == 0) attron(COLOR_PAIR(1) | A_DIM);
        else attron(COLOR_PAIR(1));
        
        printw(" ");

        if (i % 2 == 0) attroff(COLOR_PAIR(1) | A_DIM);
        else attroff(COLOR_PAIR(1));
    }

    getch();

    endwin();
    
    return 0;
}
