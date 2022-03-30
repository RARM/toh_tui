// academic_handler.cpp -- Run the program in "Academic" mode.

/*
* About Academic Mode
* This mode does not use ncurses. The game works like the example
* given by the professor in the start document of the journey folder.
*/
#include <iostream>
#include "academic_handler.h"

void run_academic() {


    return;
}

Academic_Handler::Academic_Handler()
    : game{}, moves{ 0 } {
    // Initialize screen.
    for (size_t i{ 0 }; i < Academic_Handler::screen_height; i++)
        for (size_t j{ 0 }; j < Academic_Handler::screen_width; j++) screen[i][j] = ' ';

    // Letter A, B, and C are in the base of each rod.
    screen[Academic_Handler::screen_height - 1][Academic_Handler::id_spacing + (Academic_Handler::tower_width / 2) + 1] = 'A';
    screen[Academic_Handler::screen_height - 1][Academic_Handler::ft_spacing + Academic_Handler::id_spacing * 2 + Academic_Handler::tower_width + (Academic_Handler::tower_width / 2) + 1] = 'B';
    screen[Academic_Handler::screen_height - 1][Academic_Handler::ft_spacing * 2 + Academic_Handler::id_spacing * 3 + Academic_Handler::tower_width * 2 + (Academic_Handler::tower_width / 2) + 1] = 'C';
}
