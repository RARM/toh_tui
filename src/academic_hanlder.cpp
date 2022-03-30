// academic_handler.cpp -- Run the program in "Academic" mode.

/*
* About Academic Mode
* This mode does not use ncurses. The game works like the example
* given by the professor in the start document of the journey folder.
*/
#include <iostream>
#include "academic_handler.h"

void run_academic() {
    std::cout << "Hello world!" << std::endl;

    return;
}

/*
* Academic_Handler Constructor
* Precondition: None.
* Postcondition: A new game context is created.
*/
Academic_Handler::Academic_Handler()
    : game{} {
    this->clear_screen();
}

/*
* Academic_Handler Display Towers
* Precondition: None.
* Postcondition: The Towers of Hanoi are displayed to cout.
*/
void Academic_Handler::display() {
    this->clear_screen();
    this->update_screen();
}

/*
* Academic_Handler Try Move
* Precondition: The source and destination are given as arguments (using ToH_Game constants).
* Postcondition: Returns one of the AHMC codes representing the
* error or success during the move. If there is an error, no move will happen.
*/
int Academic_Handler::try_move(int src, int dst) {
    int code;
    bool moved;

    std::tie(moved, code) = this->game.move(src, dst);

    switch (code)
    {
    case ToH_Game::MC1:
        code = Academic_Handler::AHMC1;
        break;
    case ToH_Game::MC2:
        code = Academic_Handler::AHMC2;
        break;
    default:
        code = Academic_Handler::AHMC0;
        break;
    }

    return code;
}

/*
* Academic_Handler Update Screen
* Precondition: None.
* Postcondition: The screen is updated to represent the current
* state of the game. This could be use to display to an outstream.
*/
void Academic_Handler::update_screen() {
    Rods state{ this->game.get_state() };


}

/*
* Academic_Handler Clear Screen
* Precondition: None.
* Postcondition: The screen context is cleared.
*/
void Academic_Handler::clear_screen() {
    // Initialize/clear screen.
    for (size_t i{ 0 }; i < Academic_Handler::screen_height; i++)
        for (size_t j{ 0 }; j < Academic_Handler::screen_width; j++) screen[i][j] = ' ';

    // Letter A, B, and C are in the base of each rod.
    screen[Academic_Handler::screen_height - 1][Academic_Handler::id_spacing + (Academic_Handler::tower_width / 2) + 1] = 'A';
    screen[Academic_Handler::screen_height - 1][Academic_Handler::ft_spacing + Academic_Handler::id_spacing * 2 + Academic_Handler::tower_width + (Academic_Handler::tower_width / 2) + 1] = 'B';
    screen[Academic_Handler::screen_height - 1][Academic_Handler::ft_spacing * 2 + Academic_Handler::id_spacing * 3 + Academic_Handler::tower_width * 2 + (Academic_Handler::tower_width / 2) + 1] = 'C';
}