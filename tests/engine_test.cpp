// engine_test.cpp -- Unit test for the ToH_Game object.
#include <iostream>
#include "game_engine.h"

int main(void) {
    ToH_Game engine;

    // Get the state of the game.
    Rods state{ engine.get_state() };

    // Moves to solve a 3 rods game.
    engine.move(ToH_Game::rod_A, ToH_Game::rod_C);
    engine.move(ToH_Game::rod_A, ToH_Game::rod_B);
    engine.move(ToH_Game::rod_C, ToH_Game::rod_B);
    engine.move(ToH_Game::rod_A, ToH_Game::rod_C);

    // Update the state of the game.
    state = engine.get_state();

    engine.move(ToH_Game::rod_B, ToH_Game::rod_A);
    engine.move(ToH_Game::rod_B, ToH_Game::rod_C);
    engine.move(ToH_Game::rod_A, ToH_Game::rod_C);

    // All the disks should be in rod C now.
    state = engine.get_state();

    std::cout << "Test: " << ((engine.is_solved()) ? "passed" : "failed") << "." << std::endl;

    // Let's try to make some illegal moves.
    bool moved;
    int code;

    // This should set moved to false and code to 3.
    std::tie(moved, code) = engine.move(ToH_Game::rod_A, ToH_Game::rod_B);

    // This should keep moved to false and set code to 4.
    std::tie(moved, code) = engine.move(4, 5);

    // This should set moved to true and code to 1.
    std::tie(moved, code) = engine.move(ToH_Game::rod_C, ToH_Game::rod_B);

    // This should set moved to false and code to 2.
    std::tie(moved, code) = engine.move(ToH_Game::rod_C, ToH_Game::rod_B);

    return 0;
}