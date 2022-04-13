// The full handler uses ncurses to run the game.
#ifndef _FULL_HANDLER_H_
#define _FULL_HANDLER_H_

#include "game_engine.h"
#include <ncurses.h>

#include <chrono>

// Run game in "Full" mode.
void run_full();

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
    // Time members.
    std::chrono::duration<std::chrono::system_clock::rep> saved_duration;   // saved for a paused game
    std::chrono::time_point<std::chrono::system_clock> start_time;          // for duration calculations
    std::chrono::duration<int> seconds; // total time: seconds (up to 60)
    std::chrono::duration<int> minutes; // total time: minutes

    // Game mechanics members.
    ToH_Game game_engine;   // instance of the game mechanics
    bool holding_disk;      // flag for displaying source as holded (for the tui)
    int disk_pos;   // a ToH_Game::rod_ representing the position where the source disk is being holded
    int src_disk;   // a ToH_Game::rod_ constant representing the source disk
    int dst_disk;   // a ToH_Game::rod_ constant representing the destination disk

    // Calculate and save the time (minutes and seconds) based on the start_time + saved duration.
    void update_time_elapsed();

    // Draw the game in the screen based on member values.
    void draw();

    // Process user input (update game values) or do nothing if NULL.
    void process(int key_input);

public:
    Round(size_t amount_of_disks = 3);
    ~Round();

    // Play the round (from start to puzzle solved).
    void play();

    // Save the game state. (To be implemented.)
    // Game_Data save();
};

#endif