// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "connect_four_action.hpp"

ConnectFourAction::ConnectFourAction(const bool next_turn, const unsigned row,
                                     const unsigned column)
    : next_turn(next_turn), row(row), column(column) {}

std::string ConnectFourAction::serialize() const {
    return std::to_string(column);
}
