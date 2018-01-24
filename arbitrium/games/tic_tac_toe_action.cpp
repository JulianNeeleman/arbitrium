// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "tic_tac_toe_action.hpp"

TicTacToeAction::TicTacToeAction(const unsigned next_turn, const unsigned i,
                                 const unsigned j)
    : Action(next_turn), i(i), j(j) {}

std::string TicTacToeAction::serialize() const {
    return "place token on (" + std::to_string(i) + ", " + std::to_string(j) +
           ")";
}

