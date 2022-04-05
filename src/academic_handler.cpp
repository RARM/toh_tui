// academic_handler.cpp -- Run the program in "Academic" mode.

/*
* About Academic Mode
* This mode does not use ncurses. The game works like the example
* given by the professor in the start document of the journey folder.
*/
#include "academic_handler.h"
#include <cstdio> // To wait for character at the end.

/*
* Helper function. Given a character, returns the symbol representing
* a rod for the game. It returns -1 if the letter is not valid.
*/
int c_to_s(char letter) {
    int rod;

    switch (letter)
    {
    case 'A':
    case 'a':
        rod = ToH_Game::rod_A;
        break;
    case 'B':
    case 'b':
        rod = ToH_Game::rod_B;
        break;
    case 'C':
    case 'c':
        rod = ToH_Game::rod_C;
        break;
    default:
        rod = -1;
    }

    return rod;
}

/*
* Helper function. Read the standard input for a character that
* actually represents a rods for the game.
*/
int get_rod() {
    char user_input;

    do {
        std::cin >> user_input;
    } while (user_input == ' ' || user_input == '\t'); // in case it extracts a whitespace (it shouldn't?)

    return c_to_s(user_input);
}

/*
* Helper function. Returns two integers representing the source and
* destination rods based on the letters input.
*/
std::tuple<int, int> get_user_input() {
    int out_src, out_dst;
    bool valid_symbols;

    do {
        out_src = get_rod();
        out_dst = get_rod();
        valid_symbols = out_src != -1 && out_dst != -1;

        if (!valid_symbols) std::cout << "Invalid rods. Please, try again: ";
    
        // std::cin.clear();   // Clears any errors.
        std::cin.ignore();  // Discards the buffer.
    } while (!valid_symbols);

    return std::make_tuple(out_src, out_dst);
}

/*
* Main routine for the Academic version.
* This manages the interfaces with the user.
*/
void run_academic() {
    Academic_Handler handler;
    int src, dst, move_code;
    
    std::cout << "Welcome to the Tower of Hanoi game.\n"
              << "There are three disks. All of them are in the rod A.\n"
              << "You win when you move all the disks to the rod C.\n\n";

    while (!handler.solved()) {
        std::cout << handler << "\n"; // Print the state of the game.

        std::cout << "Give the source stack (A, B, or C) and destination stack separated by 1 space.\n"
                  << "What is your move? " << std::flush;

        std::tie(src, dst) = get_user_input();
        move_code = handler.try_move(src, dst);

        if (move_code == Academic_Handler::AHMC2) std::cout << "\nCan't cheat!\n";

        std::cout << std::endl;
    }

    std::cout << handler << "\n";

    if (handler.best_sol() == handler.get_moves()) std::cout << "Can't do better than that!";
    else std::cout << "Won in " << handler.get_moves() << " moves!";

    std::cout << std::endl;

    std::cout << "\n\nClick <enter> to exit.\n";
    
    // std::cin.ignore(); Not needed for just one <enter>.
    std::getchar();
    
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
std::ostream& operator<<(std::ostream& os, Academic_Handler& handler) {
    handler.clear_screen();
    handler.update_screen_mem();

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
    constexpr size_t y_pos{ Academic_Handler::screen_height - 1 };
    constexpr size_t letter_pos{ Academic_Handler::id_spacing + (Academic_Handler::tower_width / 2) };
    constexpr size_t total_tower_width{ Academic_Handler::ft_spacing + Academic_Handler::id_spacing + Academic_Handler::tower_width };

    screen[y_pos][letter_pos] = 'A';
    screen[y_pos][total_tower_width + letter_pos] = 'B';
    screen[y_pos][total_tower_width * 2 + letter_pos] = 'C';
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
    size_t y_pos{ origin.y }, x_pos{ origin.x };
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