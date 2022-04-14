#include "full_handler.h"

/* Full Run
 * Precondition: None.
 * Postcondition: This subroutine uses all the elements in the Full_Handler library to run an instance of the ToH_TUI game.
 */
void run_full() {
    // TESTING.
    Round game("Rodolfo", 5);

    initscr();

    game.play();

    endwin();

    return;
}

/* Round Constructor
 * Precondition: The amount of disks used for this game round is given as the argument (it must fit in the current stdscr space).
 * Postcondition: It populates the esential members of the class preparing for the game.
 */
Round::Round(const std::string& player_name, const size_t& amount_of_disks, int fps)
    : game_engine{ amount_of_disks }, player_name{ player_name }, refresh_rate{ fps } {

        // saved_duration: This will be implemented later. This is used to restore a saved game.
        this->saved_duration = std::chrono::duration<std::chrono::system_clock::rep>(0); 

        // Game mechanics initialization.
        this->holding_disk = false;
        this->disk_pos = ToH_Game::rod_A;
        this->src_rod = ToH_Game::rod_NULL;
        this->dst_rod = ToH_Game::rod_NULL;
    }

/* Round Class: play
 * Precondition: The ncurses must be initialized (initscr()).
 * Postcondition:
 * 
 * This subroutine takes care of running the game calling the different private members of this class.
 */
void Round::play() {
    int user_input;

    // Start game variables.
    this->start_time = std::chrono::system_clock::now(); // The game is starting now.
    
    clear(); // blank whiteboard
    this->init_scrns();

    // Set game configurations.
    timeout(1000 / this->refresh_rate);
    curs_set(0); // invisible cursor

    // Playing.
    this->draw();

    this->done = false;
    while (!this->done) {
        user_input = getch();
        this->process(user_input);
        this->draw();
    }

    this->del_scrns();

    return;
}

/* Round Class:: init_scrns
 * Precondition: The WINDOW pointers must be uninitialized. Disks must fit in the current stdscr size.
 * Postcondition: It loads the game layout screen based on the game dimensions. It also saves the different window dimensions in the respective members.
 */
void Round::init_scrns() {
    // Initializing the info bar.
    this->iw_dimensions.width = COLS;
    this->iw_dimensions.height = 1;
    this->info_window = newwin(this->iw_dimensions.height, this->iw_dimensions.width, 0, 0); // top

    // Initialize the controls board.
    this->cbw_dimensions.height = 3;
    this->cbw_dimensions.width = COLS - 2; // a border space on each side
    int cbw_starty = LINES - this->cbw_dimensions.height - 1;
    this->controls_board_window = newwin(this->cbw_dimensions.height, this->cbw_dimensions.width, cbw_starty, 1);

    // Initialize the rods and disks window.
    int disks_num = this->game_engine.get_disk_num(); // amount of disks
    int largest_disk_width = Round::get_disk_dimension(disks_num);
    this->dw_dimensions.width = 3 * largest_disk_width + 4; // 4 because there is a space in between each rod
    this->dw_dimensions.height = disks_num + 3;

    int dw_starty = cbw_starty - 1 - this->dw_dimensions.height;
    int dw_startx = (COLS - this->dw_dimensions.width) / 2; // for horizontal centering

    this->disks_window = newwin(this->dw_dimensions.height, this->dw_dimensions.width, dw_starty, dw_startx);

    this->ncurses_setup();

    return;
}

/* Round: ncurses_setup
 * Precondition: None.
 * Postcondition: Initializes the colors used throughout the game if they haven't been already.
 */
void Round::ncurses_setup() {
    keypad(stdscr, TRUE);

    // FIXME: add colors.
    start_color();
    init_pair(Round::color_board, COLOR_BLACK, COLOR_WHITE);   // black letters, white background
    init_pair(Round::color_disk, COLOR_BLACK, COLOR_CYAN);   // black letters, blue background

    return;
}

/* Round: del_scrns
 * Precondition: All the internal windows (layout) must be initialized.
 * Postcondition: Frees all the windows memory.
 */
void Round::del_scrns() {
    delwin(this->info_window);
    delwin(this->disks_window);
    delwin(this->controls_board_window);

    refresh();
}

/* Round: draw
 * Precondition: Screens must be initialized.
 * Postcondition: It calls all the other draw subroutines to draw the game.
 */
void Round::draw() {
    this->draw_controls_board();

    this->draw_disks();

    this->update_time_elapsed();
    this->draw_info();

    return;
}

/* Round: update_time_elapsed
 * Precondition: The start_time and saved_duration must be initialized.
 * Poscondition: Update the total minutes and seconds accordingly.
 */
void Round::update_time_elapsed() {
    std::chrono::duration<std::chrono::system_clock::rep> total_seconds = 
        std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start_time) +
        this->saved_duration;
    
    this->seconds = total_seconds.count() % 60;
    this->minutes = total_seconds.count() / 60;

    return;
}

/* Round: draw_info
 * Precondition: The update_time_elapsed must have been called before this to have accurate time readings.
 * Postcondition: It draws the top bar of the game.
 */
void Round::draw_info() {
    std::string sec_str;
    std::string min_str;

    werase(this->info_window);

    // Draw the name.
    mvwprintw(this->info_window, 0, 0, " Player: %s", this->player_name.c_str());

    // Right corner.
    std::string right_corner = "Moves: "; // Getting the moves.
    right_corner += std::to_string(game_engine.get_moves());
    right_corner += "/";
    right_corner += std::to_string(game_engine.opt_sol());

    right_corner += " | Time: ";
    
    min_str = std::to_string(this->minutes);
    right_corner += (min_str.size() < 2) ? "0" + min_str : min_str;
    right_corner += ":";
    
    sec_str = std::to_string(this->seconds);
    right_corner += (sec_str.size() < 2) ? "0" + sec_str : sec_str ; // padding
    right_corner += " ";

    // Drawing right corner info.
    mvwprintw(this->info_window, 0, this->iw_dimensions.width - right_corner.size(), "%s", right_corner.c_str());
    wrefresh(this->info_window);

    return;
}

/* remove_first
 * Precondition: A vector is given as argument.
 * Postcondition: All elements are moven down 1 space and the lastone poped.
 * 
 * This is used in removing the holded disk from the stack.
 */
void remove_first(std::vector<unsigned>& v) {
    for (size_t i{ 0 }; i < v.size() - 1; i++)
        v.at(i) = v.at(i + 1);
    
    v.pop_back();
}

/* get_disk_rep
 * Precondition: An integer representing the disk ID is given as argument.
 * Postcondition: A string representing the drawing of the disk is returned.
 */
std::string get_disk_rep(unsigned disk_id) {
    std::string disk_rep;
    std::string disk_num;
    int disk_width{ Round::get_disk_dimension(disk_id) };

    for (int i{ disk_width }; i > 0; i--) disk_rep += " ";

    // Print the number in the disk.
    disk_num = std::to_string(disk_id);
    for (unsigned i{ 0 }; i < disk_num.size(); i++) disk_rep.at(disk_rep.size() / 2 + i) = disk_num.at(i);

    return disk_rep;
}

/* Round: draw_disks
 * Precondition: All game mechanics members must be initialized.
 * Postcondition: Draws all the disks and game in the disks_window.
 */
void Round::draw_disks() {
    // FIXME: complete implementation
    std::string board_base;
    int rod_A_pos, rod_B_pos, rod_C_pos; // horizontal positions
    int hold_pos; // hold position
    unsigned hold_disk_id; // id representing the holded disk
    Rods board_state{ this->game_engine.get_state() };

    int disks_num = this->game_engine.get_disk_num(); // amount of disks
    int largest_disk_width = Round::get_disk_dimension(disks_num);

    werase(this->disks_window); // CLEAR WINDOW

    // Get the position of the rods (horizontally).
    rod_A_pos = 1 + largest_disk_width / 2;
    rod_B_pos = rod_A_pos + largest_disk_width + 1;
    rod_C_pos = rod_B_pos + largest_disk_width + 1;

    // Draw board.
    for (int i{ 0 }; i < this->dw_dimensions.width; i++) // get a string the same length of the base
        board_base += " ";
    
    wattron(this->disks_window, COLOR_PAIR(Round::color_board) | A_DIM); // dimmed white color
    mvwprintw(this->disks_window, this->dw_dimensions.height - 1, 0, "%s", board_base.c_str());
    mvwprintw(this->disks_window, this->dw_dimensions.height - 1, rod_A_pos, "A");
    mvwprintw(this->disks_window, this->dw_dimensions.height - 1, rod_B_pos, "B");
    mvwprintw(this->disks_window, this->dw_dimensions.height - 1, rod_C_pos, "C");
    wattroff(this->disks_window, COLOR_PAIR(Round::color_board) | A_DIM); // dimmed white color

    // Rods
    for (size_t i{ 0 }; i <= this->game_engine.get_disk_num(); i++) mvwprintw(this->disks_window, this->dw_dimensions.height - 2 - i, rod_A_pos, "I");
    for (size_t i{ 0 }; i <= this->game_engine.get_disk_num(); i++) mvwprintw(this->disks_window, this->dw_dimensions.height - 2 - i, rod_B_pos, "I");
    for (size_t i{ 0 }; i <= this->game_engine.get_disk_num(); i++) mvwprintw(this->disks_window, this->dw_dimensions.height - 2 - i, rod_C_pos, "I");

    // Draw holded row or signal character.
    switch (this->disk_pos)
    {
    case ToH_Game::rod_A:
        hold_pos = rod_A_pos;
        break;
    
    case ToH_Game::rod_B:
        hold_pos = rod_B_pos;
        break;
    
    case ToH_Game::rod_C:
        hold_pos = rod_C_pos;
        break;
    }

    if (this->holding_disk) { // reusing board_base to draw the disk
        switch (this->src_rod) {
        case ToH_Game::rod_A:
            board_base = get_disk_rep(board_state.A.at(0));
            hold_disk_id = board_state.A.at(0);
            break;
        
        case ToH_Game::rod_B:
            board_base = get_disk_rep(board_state.B.at(0));
            hold_disk_id = board_state.B.at(0);
            break;
        
        case ToH_Game::rod_C:
            board_base = get_disk_rep(board_state.C.at(0));
            hold_disk_id = board_state.C.at(0);
            break;
        }
        
        if (hold_disk_id % 2 == 0) wattron(this->disks_window, COLOR_PAIR(Round::color_disk) | A_DIM);
        else wattron(this->disks_window, COLOR_PAIR(Round::color_disk));

        mvwprintw(this->disks_window, 0, hold_pos - board_base.size() / 2, "%s", board_base.c_str());

        if (hold_disk_id % 2 == 0) wattroff(this->disks_window, COLOR_PAIR(Round::color_disk) | A_DIM);
        else wattroff(this->disks_window, COLOR_PAIR(Round::color_disk));

    } else
        mvwprintw(this->disks_window, 0, hold_pos, "^");

    // Printing the disks in the roads.
    if (this->holding_disk) {
        switch (this->src_rod) {
        case ToH_Game::rod_A:
            remove_first(board_state.A);
            break;
        
        case ToH_Game::rod_B:
            remove_first(board_state.B);
            break;
        
        case ToH_Game::rod_C:
            remove_first(board_state.C);
            break;
        }
    }

    this->draw_rod_disks(rod_A_pos, board_state.A);
    this->draw_rod_disks(rod_B_pos, board_state.B);
    this->draw_rod_disks(rod_C_pos, board_state.C);

    wrefresh(this->disks_window);

    return;
}

/* Round: draw_rod_disks
 * Precondition: The position of the rod (horizontally) and the vector representing the disks must be given as arguments.
 * Postcondition: It updates the disks_window to contain the disks. It does not refresh the window.
 */
void Round::draw_rod_disks(const int& rod_pos, std::vector<unsigned>& disks) {
    int disk_width;
    std::string disk_rep;
    
    for (size_t i{ disks.size() }; i > 0; i--) {
        disk_width = Round::get_disk_dimension(static_cast<int>(disks.at(i - 1)));
        disk_rep =  get_disk_rep(disks.at(i - 1));

        if (disks.at(i - 1) % 2 == 0) wattron(this->disks_window, COLOR_PAIR(Round::color_disk) | A_DIM); // for different color disks
        else wattron(this->disks_window, COLOR_PAIR(Round::color_disk));
        
        mvwprintw(this->disks_window, this->dw_dimensions.height - 2 - (disks.size() - i), rod_pos - disk_width / 2, "%s", disk_rep.c_str());

        if (disks.at(i - 1) % 2 == 0) wattroff(this->disks_window, COLOR_PAIR(Round::color_disk) | A_DIM);
        else wattroff(this->disks_window, COLOR_PAIR(Round::color_disk));
    }
}

/* Round: draw_controls_board
 * Precondition: Mechanics member variables must be initialized.
 * Postcondition: Draws the control_board_window.
 */
void Round::draw_controls_board() {
    // FIXME: implement
    return;
}

/* Round: process
 * Precondition: A key must be given as input.
 * Postcondition: Updates the game based on the input.
 */
void Round::process(int key_input) {
    Rods game_state{ this->game_engine.get_state() };
    
    switch (key_input)
    {
    case KEY_RIGHT:
        this->disk_pos += (this->disk_pos == ToH_Game::rod_C) ? 0 : 1;
        break;

    case KEY_LEFT:
        this->disk_pos -= (this->disk_pos == ToH_Game::rod_A) ? 0 : 1;
        break;
    
    case '\n': // enter
        if (this->holding_disk) { // make the move
            this->game_engine.move(this->src_rod, this->disk_pos);
            this->holding_disk = false;
        } else {
            switch (this->disk_pos) { // save the id of the src rod
            case ToH_Game::rod_A:
                this->src_rod = (game_state.A.size() > 0) ? ToH_Game::rod_A : ToH_Game::rod_NULL;
                break;
            case ToH_Game::rod_B:
                this->src_rod = (game_state.B.size() > 0) ? ToH_Game::rod_B : ToH_Game::rod_NULL;
                break;
            case ToH_Game::rod_C:
                this->src_rod = (game_state.C.size() > 0) ? ToH_Game::rod_C : ToH_Game::rod_NULL;
                break;
            }

            this->holding_disk = (this->src_rod != ToH_Game::rod_NULL) ? true : false;
        }
        break;

    case 'a':
    case 'A':
        break;
    
    case 'q':
    case 'Q':
        this->done = true;
        break;
    }
    return;
}

/* Round: get_disk_dimension
 * Precondition: A disk id must be given as argument.
 * Postcondition: The width of the disk is returned.
 */
int Round::get_disk_dimension(int disk_number) {
    return disk_number * 4 - 1; // width of the disk
}