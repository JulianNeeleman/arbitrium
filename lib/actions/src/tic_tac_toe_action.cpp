#include "../include/tic_tac_toe_action.hpp"

unsigned TicTacToeAction::get_i() const { return i_; }
unsigned TicTacToeAction::get_j() const { return j_; }

TicTacToeAction::TicTacToeAction(unsigned i, unsigned j) : i_(i), j_(j) {}

std::string TicTacToeAction::serialize() const {
    return "place token on (" + std::to_string(i_) + ", " + std::to_string(j_) +
           ")\n";
}
