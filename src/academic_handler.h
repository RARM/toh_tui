#ifndef _ACADEMIC_HANDLER_H_
#define _ACADEMIC_HANDLER_H_

#include "game_engine.h"

// Run game in "Academic" mode.
void run_academic();

class Academic_Handler
{
public:
	// Setup the game.
	// Academic_Handler();

	// Display current game state (disks in rods).
	// void display();

	// The main function can make direct calls to the ToH_Game object.
	// friend void run_academic();

private:
	ToH_Game game;
	size_t moves;
};

#endif