#ifndef _ACADEMIC_HANDLER_H_
#define _ACADEMIC_HANDLER_H_

#include "game_engine.h"

// Run game in "Academic" mode.
void run_academic();

class Academic_Handler
{
public:
	// Setup the game.
	Academic_Handler();

	// Display current game state (disks in rods) and prompt for next roung (or game over).
	// void display();

	// Make move using ToH_Game constants.
	// int try_move(int src, int dst);

private:
	// screen calculations
	static constexpr size_t screen_height{ 4 }; // how tall the screen is going to be
	static constexpr size_t tower_width{ 5 }; // the width occupied by the towers
	static constexpr size_t id_spacing{ 2 }; // width of the ids representing the towers on the left
	static constexpr size_t ft_spacing{ 6 }; // total space between towers after id_spacing is added (full tower spacing)
	static constexpr size_t screen_width{ (tower_width + id_spacing) * 3 + ft_spacing * 2 }; // newline not included

	// members
	ToH_Game game;
	size_t moves;
	char screen[screen_height][screen_width];

	// Helper functions.

	// Update the screen content for display using current state.
	// void update_screen();

	// Remove any characters from the rods that represent the disks.
	// void clear_screen();
};

#endif