// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "tic_tac_toe_action.hpp"

TicTacToeAction::TicTacToeAction(const bool next_turn, const unsigned row,
                                 const unsigned column)
    : next_turn(next_turn), row(row), column(column) {}

std::string TicTacToeAction::serialize() const {
    return "place token on (" + std::to_string(row) + ", " + std::to_string(column) +
           ")";
}
