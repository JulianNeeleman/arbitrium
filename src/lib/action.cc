#include "include/lib/action.h"

Action::Action(unsigned player) : player_(player) {}

/**
 * Get the index of the player who is subject to this action.
 */
int Action::get_player() const { return player_; }
