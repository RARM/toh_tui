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
    int src_rod;   // a ToH_Game::rod_ constant representing the source rod
    int dst_rod;   // a ToH_Game::rod_ constant representing the destination rod
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

    // Setup ncurses variables like colors. Call only once after ncurses initialization.
    void ncurses_setup();

    // Destroy all windows (layout).
    void del_scrns();

    // Draw the game in the screen based on member values. (Note: ncurses color pairs 10-11 are reserved for the draw functions.)
    void draw();

    // Draws info_bar window. 
    void draw_info();

    // Draw the rods and disks in the disks_window and refresh.
    void draw_disks();

    // Routine for drawing the disks in a rod.
    void draw_rod_disks(const int& rod_pos, std::vector<unsigned>& disk_ids);

    // Draw the information in the controls_board_window and refresh.
    void draw_controls_board();

    // Color constants. Used for styles.
    static constexpr short color_board{ 10 };  // used for the board
    static constexpr short color_disk{ 11 };   // used for the disks

    // Process user input (update game values) or do nothing if NULL.
    void process(int key_input);

    // Setup source disk based on rod_position.
    void set_src();

public:
    // Round constructor.
    Round(const std::string& player_name, const size_t& amount_of_disks = 3, int fps = 10);

    // Play the round (from start to puzzle solved).
    void play();

    // Get the disk dimension. Used moslty for graphic calculations.
    static int get_disk_dimension(int disk_num);

    // Get maximum amount of disks possible for the current screen size.
    static unsigned get_maximum_disks();

    // Save the game state. (To implement later.)
    // Game_Data save();
};

/* Full Handler
 * Simple interface to initialize and manage the game (e.g. game main menu and setup).
 */
class Full_Handler
{
private:
    // Game data.
    std::string player_name;
    unsigned disks_amount;
    
    // Windows handlers.
    int cursor_position;

    // Helper functions.

    // Draw banne for the main menu.
    void mm_banner_draw(WINDOW* banner_win);

    // Draw menu based on the cursor position.
    void mm_draw_selection(WINDOW* selection_win);

    // Color pair used for ncurses drawings (Full_Handler reserves pairs 1 to 5);
    static constexpr short color_banner{ 1 };   // used to display the banner in the main menu
    static constexpr short color_menu_sel{ 2 }; // used to display the selector arrow in the main menu

    // Draw the setup menu.
    void sm_draw(WINDOW* setup_window);
public:
    Full_Handler();
    ~Full_Handler();

    // Display the main menu. Returns a constant representing the current selection.
    int main_menu();

    // Selection constants.
    static constexpr int MM_Play{ 1 };
    static constexpr int MM_About{ 2 };
    static constexpr int MM_Exit{ 3 };
    static constexpr int MM_Setup{ 4 };

    // Diplay the setup screen. Updates the game data values.
    void setup();

    // Cursor position for the setup menu.
    static constexpr int SM_Name{ 1 };
    static constexpr int SM_Disks{ 2 };
    static constexpr int SM_Go{ 3 };

    // Start a game. Uses the game data in the object to call the game.
    void play();

    // Display the "About" information.
    // void about();
};

#endif