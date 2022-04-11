// The full handler uses ncurses to run the game.
#ifndef _FULL_HANDLER_H_
#define _FULL_HANDLER_H_

#include "game_engine.h"
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

// Run game in "Full" mode.
void run_full();

// Used to keep all the dimensions of a window in a single structure.
typedef struct {
	size_t startx = 0,
	       starty = 0,
		   width  = 0,
		   height = 0;
} Window_Dimensions_Struct;

// Used to share keep points in the screen.
typedef struct {
	size_t x = 0,
		   y = 0;
} FH_Point_Struct;

// Game configuration to setup game.
typedef struct {
	size_t max_disk = 0,
		   num_disk_selected = 0;
	std::string player_name;
} Game_Config_Struct;

class Full_Handler
{
public:
	// Setup the game.
	Full_Handler();

	// The three rule of three. Is it necessary?
	~Full_Handler();

	// Manages a round.
	// void run_round();

	// Game solved? Returns true if so.
	bool solved() { return this->game->is_solved(); }

	// Main Menu options.
	static constexpr int MM_Exit{ 0 };
	static constexpr int MM_Play{ 1 };
	static constexpr int MM_Licenses{ 2 };
	// static constexpr int MM_About{ 3 }; // Maybe implement this later.

private: 
	char src_sel, dst_sel;
	ToH_Game* game;
	std::string player_name;
	
	int sel_input_state; // Represents the current input state.

	// Selection inputs (for representing input states).
	static constexpr int si_src{ 0 };
	static constexpr int si_dst{ 1 };
	static constexpr int si_go{ 2 };

	// For screen dimensions calculation.
	static constexpr size_t info_panel_height{ 3 };

	// Helper functions.

	// Display setup questions. How many disks would you like to play with?
	Game_Config_Struct get_game_setup();

	// Get the maximum number of disks that can be used based on the current window size.
	size_t get_maximum_nums_of_disks();

	// Dispaly current state of the rods.
	// void display_rods_state();

	// Display help info.
	// void display_help();

	// Display current selection for the move.
	// void display_selection();

	// This will update selection characters and call display_selection.
	// void get_move();
};

#endif