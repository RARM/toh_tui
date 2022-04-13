#include "full_handler.h"

/* Full Run
 * Precondition: None.
 * Postcondition: This subroutine uses all the elements in the Full_Handler library to run an instance of the ToH_TUI game.
 */
void full_run() {
    return;
}

/* Round Constructor
 * Precondition: The amount of disks used for this game round is given as the argument.
 * Postcondition: It populates the esential members of the class preparing for the game.
 */
Round::Round(const std::string& player_name, const size_t& amount_of_disks)
    : game_engine{ amount_of_disks }, player_name{ player_name } {}
