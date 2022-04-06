#include "full_handler.h"

/*
* Precondition: A vector of strings is given as an argument.
* Postcondition: The largest width is returns as a size_t.
*/
size_t longest_str(const std::vector<std::string>& str_arr) {
    size_t longest{ 0 };

    for (size_t i{ 0 }; i < str_arr.size(); i++) // search for the longest width
        longest = (longest < str_arr.at(i).size()) ? str_arr.at(i).size() : longest;

    return longest;
}

/*
* Build the list of options for the main menu.
* Precondition: None.
* Postcondition: Returns a vector of strings with all the possible options for the main menu.
*/
std::vector<std::string> generate_options_vector() {
    return std::vector<std::string> {
        "Play",
        "Licenses",
        "Exit"
    };
}

/*
* Calculate all the dimensions for the main menu.
* Precondition: The stdscr must have been already initialized.
* Postcondition: Returns a Window_Dimensions_Struct object with all the calculated required dimensions to
* hold the given the array of options.
*/
Window_Dimensions_Struct calculate_menu_dims(const std::vector<std::string>& opts) {
    Window_Dimensions_Struct dimensions;

    // Calculate dimensions with padding.
    dimensions.width = longest_str(opts) + 6;
    dimensions.height = opts.size() + 4;

    // Calculate position to center.
    dimensions.startx = (COLS - dimensions.width) / 2;
    dimensions.starty = (LINES - dimensions.height) / 2;

    return dimensions;
}

/*
* Draw the menu window.
* Precondition: Give the arguments "Window_Dimensions_Struct", options, and current_selection.
* Postcondition: Creates and draws the menu window given the options, dimensions, and selection. 
*/
WINDOW* create_and_draw_menu(const Window_Dimensions_Struct& dimensions, const std::vector<std::string>& options, const size_t& selection) {
    WINDOW* win = newwin(dimensions.height, dimensions.width, dimensions.starty, dimensions.startx);

    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+'); // draw the box borders

    // print the menu options
    for(size_t i{ 0 }; i < options.size(); i++)
        for(size_t char_pos{ 0 }; char_pos < options.at(i).size(); char_pos++)
            mvwaddch(win, 2 + i, 4 + char_pos, options.at(i).at(char_pos));

    // print the arrow to show current selection
    mvwprintw(win, selection + 1, 2, "->");

    // display the window
    refresh();
    wrefresh(win);

    return win;
}

/*
* Main Menu
* Precondition: None.
* Postcondition: Returns a Full_Handler::MM_ constant represnting the option choosen.
*
* This subroutine will take care of displaying the main menu and asking for input.
* The input is processed by another subroutine.
*/
int main_menu() {
    WINDOW* menu_win;
    std::vector<std::string> options{ generate_options_vector() };
    Window_Dimensions_Struct dimensions{ calculate_menu_dims(options) };
    int user_input, menu_selection;
    size_t sel{ 1 }, sel_min{ 1 }, sel_max{ options.size() };

    // first menu draw
    menu_win = create_and_draw_menu(dimensions, options, sel);

    // Menu Driver
    while ((user_input = getch()) != '\n')
    {
        switch (user_input)
        {
        case KEY_UP:
            sel = (sel == sel_min) ? sel_min : sel - 1;
            delwin(menu_win);
            menu_win = create_and_draw_menu(dimensions, options, sel);
            break;
        
        case KEY_DOWN:
            sel = (sel == sel_max) ? sel_max : sel + 1;
            delwin(menu_win);
            menu_win = create_and_draw_menu(dimensions, options, sel);
            break;
        }
    }

    delwin(menu_win);

    // convert selection to Full_Handler::MM_ constant
    switch (sel)
    {
    case 1:
        menu_selection = Full_Handler::MM_Play;
        break;

    case 2:
        menu_selection = Full_Handler::MM_Licenses;
        break;
    
    default:
        menu_selection = Full_Handler::MM_Exit;
    }

    return menu_selection;
}

/*
* Display the licenses.
* Precondition: None.
* Postcondition: Display the licenses and exists when the user clicks <enter>.
*/
void display_licenses() {
    int user_input;
    
    mvprintw(0, 0, "Licenses...\nClick <enter> to exit.");
    refresh();

    while((user_input = getch()) != '\n');

    clear();
    refresh();
}

/*
* Full Handler Main Entry Point
* The run_full subroutine is the starting point for the full version.
* It starts by whosing a menu calling other functions based on the input.
*/
void run_full() {
    int menu_sel;
    // Full_Handler* handler;
    
    initscr();      // start ncurses
    cbreak();       // disable input buffering
    keypad(stdscr, TRUE);   // enable use of function and arrow keys
    noecho();       // no need to see input
    curs_set(0);
    refresh();      // draw that black screen

    while((menu_sel = main_menu()) != Full_Handler::MM_Exit) { // start the main menu
        clear(); // clear the screen before entering and after exiting a routine
        
        switch (menu_sel)
        {
        case Full_Handler::MM_Play:
            // handler = new Full_Handler();
            // handler->play();
            // delete handler;
            break;
        
        case Full_Handler::MM_Licenses:
            display_licenses();
            break;
        }
        
        clear();
    }
    
    endwin();       // terminate ncurses
}

/*
* Full Handler Constructor
* Precondition: ncurses must be initialized.
* Postcondition: A new game is setup. After this, call play to run the game.
*/
/* Full_Handler::Full_Handler()
    : src_sel{ NULL }, dst_sel{ NULL } {
    size_t disks{ Full_Handler::setup_disks() };
    this->game = new ToH_Game(disks);
} */