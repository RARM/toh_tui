// main.cpp -- Game driver.
// This file takes care of initilizing the game and running the respective handler.

// Compilation settings.
#define FULL_VERSION true // It will only compile the "Academic" version if false.

#include "academic_handler.h"
#if FULL_VERSION
#include "full_handler.h"
#endif

int main(void) {

#if FULL_VERSION
    char user_input;
    bool valid_input;

    std::cout << "Copyright (c) 2022 Rodolfo Andres Rivas Matta.\n"
              << "Welcome to the Tower of Hanoi Game!\n\n";
    
    do
    {
        std::cout << "==============================================\n"
                  << "Menu:\n"
                  << "1. Academic version (no TUI).\n"
                  << "2. TUI version (using ncurses).\n"
                  << "3. Exit.\n"
                  << "Enter an option: " << std::flush;
        
        std::cin >> user_input;
        valid_input = user_input == '1' || user_input == '2' || user_input == '3';
        if(!valid_input) std::cout << "Invalid input. Please, try again.\n\n";
    } while (!valid_input);

    switch (user_input)
    {
    case '1':
        std::cout << "==============================================\n\n";
        run_academic();
        break;

    case '2':
        run_full();
        break;
    }
    
#else
    run_academic();
#endif

    return 0;
}