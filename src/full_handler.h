// The full handler uses ncurses to run the game.
#ifndef _FULL_HANDLER_H_
#define _FULL_HANDLER_H_

#include "game_engine.h"
#include <ncurses.h>

#include <chrono>
#include <string>

// Run game in "Full" mode.
void run_full();


/* Point Structure
 * Used for different window calculations on the screen.
 */
typedef struct {
    int x = 0,
        y = 0;
} Point_Structure;

/* Dimensions Structure
 * Used for keeping the values of the different windows handy.
 */
typedef struct {
    int width = 0,
        height = 0;
} Dimensions_Struct;


/* Game_Data
 * Used to save a game instance for later. This mechanism is going to be implemented latter.
 */
/* typedef struct {

} Game_Data; */

/* Round Class
 * It manages the actual gameplay, and interface of a game instance.
 */
class Round
{
private:
    // Time members. These are set on the play call.
    std::chrono::duration<std::chrono::system_clock::rep> saved_duration;   // saved for a paused game
    std::chrono::time_point<std::chrono::system_clock> start_time;          // for duration calculations
    int seconds; // total time: seconds (up to 60)
    int minutes; // total time: minutes

    // Game mechanics members.
    ToH_Game game_engine;   // instance of the game mechanics
    bool holding_disk;      // flag for displaying source as holded (for the tui)
    int disk_pos;   // a ToH_Game::rod_ representing the position where the source disk is being holded
    int src_disk;   // a ToH_Game::rod_ constant representing the source disk
    int dst_disk;   // a ToH_Game::rod_ constant representing the destination disk
    std::string player_name;
    const int refresh_rate; // recommended 10 Hz
    bool done;      // used for game loop 

    // Windows for the different parts of the game.
    WINDOW* disks_window;           // disks and rods window
    WINDOW* controls_board_window;  // information below the disks window
    WINDOW* info_window;            // top bar info

    // Dimensions of the different windows (for graphics calculations on updating).
    Dimensions_Struct dw_dimensions;    // disk_window dimensions
    Dimensions_Struct cbw_dimensions;   // control_board_window dimensions
    Dimensions_Struct iw_dimensions;    // info_window dimensions

    // Calculate and save the time (minutes and seconds) based on the start_time + saved duration.
    void update_time_elapsed();

    // Initializes all the windows.
    void init_scrns();

    // Destroy all windows (layout).
    void del_scrns();

    // Draw the game in the screen based on member values.
    void draw();

    // Draws info_bar window. 
    void draw_info();

    // Draw the rods and disks in the disks_window and refresh.
    void draw_disks();

    // Draw the information in the controls_board_window and refresh.
    void draw_controls_board();

    // Process user input (update game values) or do nothing if NULL.
    void process(int key_input);

public:
    // Round constructor.
    Round(const std::string& player_name, const size_t& amount_of_disks = 3, int fps = 10);

    // Play the round (from start to puzzle solved).
    void play();

    // Get the disk dimension. Used moslty for graphic calculations.
    static int get_disk_dimension(int disk_num);

    // Save the game state. (To implement later.)
    // Game_Data save();
};

#endif