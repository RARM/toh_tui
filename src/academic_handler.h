#ifndef _ACADEMIC_HANDLER_H_
#define _ACADEMIC_HANDLER_H_

#include "game_engine.h"
#include <string>
#include <iostream>

// Run game in "Academic" mode.
void run_academic();

typedef struct Point_Struct {
	size_t x{ 0 }, y{ 0 };
} Point;

/*
* Academic Handler only works with 3 disks (id = 1, 2, and 3).
*/
class Academic_Handler
{
public:
	// Setup the game.
	Academic_Handler();

	// Draw current game state to the output stream.
	friend std::ostream& operator<<(std::ostream& os, Academic_Handler& handler);

	// Make move using ToH_Game constants.
	int try_move(int src, int dst);

	// AHMC = Academic Handler Move Codes
	static constexpr int AHMC0{ 0 }; // Unknown error.
	static constexpr int AHMC1{ 1 }; // No errors. Move perfomed.
	static constexpr int AHMC2{ 2 }; // Source disk is bigger than destination.

	// Check if the puzzle was solved.
	bool solved() { return this->game.is_solved(); }

private:
	// screen calculations
	static constexpr size_t screen_height{ 4 }; // how tall the screen is going to be
	static constexpr size_t tower_width{ 5 }; // the width occupied by the towers
	static constexpr size_t id_spacing{ 2 }; // width of the ids representing the towers on the left
	static constexpr size_t ft_spacing{ 6 }; // total space between towers after id_spacing is added (full tower spacing)
	static constexpr size_t screen_width{ (tower_width + id_spacing) * 3 + ft_spacing * 2 }; // newline not included

	// members
	ToH_Game game;
	char screen[screen_height][screen_width];

	// Helper functions.

	// Update the screen content for display using current state.
	void update_screen_mem();

	// Remove any characters from the rods that represent the disks.
	void clear_screen();

	// Draw rod in the screen memory given the origin.
	void draw_rod(Point origin, std::vector<unsigned> rod);
};

#endif