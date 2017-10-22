#include "include/tic_tac_toe/tic_tac_toe_action.h"

unsigned TicTacToeAction::get_i() const { return i_; }
unsigned TicTacToeAction::get_j() const { return j_; }

TicTacToeAction::TicTacToeAction(int player, unsigned i, unsigned j)
    : Action(player), i_(i), j_(j) {}

std::string TicTacToeAction::serialize() const {
    return "place token on (" + std::to_string(i_) + ", " + std::to_string(j_) +
           ")\n";
}
