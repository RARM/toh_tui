// academic_handler.cpp -- Run the program in "Academic" mode.

/*
* About Academic Mode
* This mode does not use ncurses. The game works like the example
* given by the professor in the start document of the journey folder.
*/
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
    : game{ 3 } {
    this->clear_screen();
}

/*
* Academic_Handler insertion operator for outstream
* Precondition: None.
* Postcondition: The content of screen is sent to the outstream.
*/
std::ostream& operator<<(std::ostream& os, const Academic_Handler& handler) {
    for (size_t y{ 0 }; y < Academic_Handler::screen_height; y++) {
        for (size_t x{ 0 }; x < Academic_Handler::screen_width; x++)
            os << handler.screen[y][x];
        os << '\n';
    }

    return os;
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
* Academic_Handler Update Screen Memory
* Precondition: None.
* Postcondition: The screen is updated to represent the current
* state of the game. This could be use to display to an outstream.
*/
void Academic_Handler::update_screen_mem() {
    Rods state{ this->game.get_state() };
    Point origin { 0, Academic_Handler::screen_height - 2 }; // height leaves a line for the letters
    constexpr size_t dist_p_twr{ Academic_Handler::id_spacing + Academic_Handler::tower_width + Academic_Handler::ft_spacing };
    
    this->draw_rod(origin, state.A);
    
    origin.x += dist_p_twr;
    this->draw_rod(origin, state.B);

    origin.x += dist_p_twr;
    this->draw_rod(origin, state.C);
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

/*
* Academic_Handler Draw Rod
* Precondition: A point representing the rod origin and the rod
* represented with a vector must be given as arguments.
* Postcondition: It draws the rod in the screen memory. If the origin
* given is outside the screen, then nothing is done.
* 
* It is assumed that no id is greater than 3 (only 3 disks) and 3 rods
* exists for this game.
*/
void Academic_Handler::draw_rod(Point origin, std::vector<unsigned> rod) {
    size_t y_pos{ origin.y }, x_pos{ origin.y };
    const size_t num_disks = rod.size();
    
    if (num_disks > 0) // update only if there is something to update
        for (size_t id_pos{ num_disks }; id_pos > 0; id_pos--) {
            // Write id.
            size_t id_i{ id_pos - 1 };
            unsigned disk_width = rod.at(id_i) + (rod.at(id_i) - 1); // special conversion id => width of disk
            std::string id_str = std::to_string(disk_width);
            this->screen[y_pos][x_pos] = id_str.at(0);

            // Draw disk.
            size_t side{ (5 - disk_width) / 2 };
            x_pos += Academic_Handler::id_spacing + side;
            for (size_t i{ 0 }; i < disk_width; i++) this->screen[y_pos][x_pos + i] = 'x';
            
            // Set next position.
            y_pos--;
            x_pos = origin.x;
        }
}