#include "full_handler.h"

/* Full Run
 * Precondition: None.
 * Postcondition: This subroutine uses all the elements in the Full_Handler library to run an instance of the ToH_TUI game.
 */
void run_full() {
    // TESTING.
    Round game("Rodolfo");

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
        this->saved_duration = std::chrono::duration<std::chrono::system_clock::rep>(0); // This will be implemented later.
        // FIXME: initialize game mechanics
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
    int larger_disk_width = Round::get_disk_dimension(disks_num);
    this->dw_dimensions.width = disks_num * larger_disk_width + 4; // 4 because there is a space in between each rod
    this->dw_dimensions.height = disks_num + 3;

    int dw_starty = cbw_starty - 1 - this->dw_dimensions.height;
    int dw_startx = (COLS - this->dw_dimensions.width) / 2; // for horizontal centering

    this->disks_window = newwin(this->dw_dimensions.height, this->dw_dimensions.width, dw_starty, dw_startx);

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

/* Round: draw_disks
 * Precondition: All game mechanics members must be initialized.
 * Postcondition: Draws all the disks and game in the disks_window.
 */
void Round::draw_disks() {
    // FIXME: implement
    return;
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
    if (key_input == 'q') this->done = true;
    // FIXME:: implement
    return;
}

/* Round: get_disk_dimension
 * Precondition: A disk id must be given as argument.
 * Postcondition: The width of the disk is returned.
 */
int Round::get_disk_dimension(int disk_number) {
    // FIXME: revise implementation for better visibility.
    return disk_number * 2 - 1;
}