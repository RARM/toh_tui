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
* Print the Game Title in the given window.
* Precondition: A pointer to the window is given in the argumetns along with the bottom left cornern position.
* Post condition: It draws the game title and author taking 6 characters tall and 36 wide.
*/
void print_game_title(WINDOW* win, FH_Point_Struct pos) {
    pos.x = pos.x - 36 / 2;

    mvwprintw(win, pos.y - 5, pos.x, " _____ ___  _   _   _____ _   _ ___\n");
    mvwprintw(win, pos.y - 4, pos.x, "|_   _/ _ \\| | | | |_   _| | | |_ _|\n");
    mvwprintw(win, pos.y - 3, pos.x, "  | || | | | |_| |   | | | | | || |\n");
    mvwprintw(win, pos.y - 2, pos.x, "  | || |_| |  _  |   | | | |_| || |\n");
    mvwprintw(win, pos.y - 1, pos.x, "  |_| \\___/|_| |_|   |_|  \\___/|___|\n");
    mvwprintw(win, pos.y,     pos.x, "   By Rodolfo Andres Rivas Matta");
    
    wrefresh(win);
    return;
}

/*
* Draw the menu window.
* Precondition: Give the arguments "Window_Dimensions_Struct", options, and current_selection.
* Postcondition: Creates and draws the menu window given the options, dimensions, and selection. 
*/
WINDOW* create_and_draw_menu(const Window_Dimensions_Struct& dimensions, const std::vector<std::string>& options, const size_t& selection) {
    WINDOW* win = newwin(dimensions.height, dimensions.width, dimensions.starty, dimensions.startx);

    FH_Point_Struct header_menu_pos {dimensions.startx + dimensions.width / 2, dimensions.starty - 2};
    print_game_title(stdscr, header_menu_pos);

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
    refresh();

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
    Full_Handler* handler;
    
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
            handler = new Full_Handler();
            // handler->play();
            delete handler;
            break;
        
        case Full_Handler::MM_Licenses:
            display_licenses();
            break;
        }
        
        clear();
    }
    
    endwin();       // terminate ncurses
}


// Unless explicitely stated, all Full Handler functions have the precondition of having ncurses initialized (it may be omitted some comments).

/*
* Full Handler Constructor
* Precondition: ncurses must be initialized.
* Postcondition: A new game is setup. After this, call play to run the game.
*/
Full_Handler::Full_Handler()
    : src_sel{ NULL }, dst_sel{ NULL } {
    Game_Config_Struct config = this->get_game_setup();
    size_t disks{ config.num_disk_selected };
    this->game = new ToH_Game(disks);
    this->player_name = config.player_name;
}

/*
* Full Handler Destructor
* Precondition: None.
* Postcondition: It frees the memory allocated for the game engine.
*/
Full_Handler::~Full_Handler() {
    delete this->game;
}

/*
* Full Handler (helper function): get_game_setup
* Precondition: ncurses must be initialized.
* Postcondition: The complete the tasks below stated. To get the starting nu
* 
* Tasks:
* - Get the maximum number of rods possible (based on the windows size).
* - Get starting number of rods.
* - Ask name (to display on the game over).
*/
Game_Config_Struct Full_Handler::get_game_setup() {
    Game_Config_Struct config;

    config.max_disk = this->get_maximum_nums_of_disks();

    return config;
}

/*
* Full Handler (helper function): get_maximum_nums_of_disks
* Precondition: ncurses must be initialized.
* Postcondition: Returns the maximum number of disks that can be used based
* on the size of the stdscr window.
*/
size_t Full_Handler::get_maximum_nums_of_disks() {
    // Horizontal calculation.
    const size_t max_disk_size_hor = (COLS - 6) / 3;         // max space
    const size_t max_disks_hor = (max_disk_size_hor + 1) / 2;  // from space to rod #

    // Vertical calculation.
    const size_t max_disks_ver = LINES - Full_Handler::info_panel_height - 6;

    return (max_disks_hor < max_disks_ver) ? max_disk_size_hor : max_disks_ver;
}