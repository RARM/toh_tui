// The full handler uses ncurses to run the game.
#ifndef _FULL_HANDLER_H_
#define _FULL_HANDLER_H_

#include "game_engine.h"

// Run game in "Full" mode.
void run_full();

class Full_Handler
{
public:
	// Setup the game.
	// Full_Handler();

	// Display setup questions. How many disks would you like to play with?
	// static size_t get_setup();

	// Manages a round.
	// void run_round();

	// Friend should be able to make direct calls to ToH_Game object.
	// friend void run_full();

private:
	ToH_Game game;
	size_t moves;
	char src_sel, dst_sel;
	
	int sel_input_state; // Represents the current input state.

	// Selection inputs (for representing input states).
	static constexpr int si_src{ 0 };
	static constexpr int si_dst{ 1 };
	static constexpr int si_go{ 2 };

	// Helper functions.

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