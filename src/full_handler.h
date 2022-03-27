#ifndef _FULL_HANDLER_H_
#define _FULL_HANDLER_H_

#include "game_engine.h"

class Full_Handler
{
public:
	Full_Handler();

private:
	ToH_Game game;
	size_t moves = 0;
};

#endif