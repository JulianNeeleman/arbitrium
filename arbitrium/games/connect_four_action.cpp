// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "connect_four_action.hpp"

ConnectFourAction::ConnectFourAction(const unsigned next_turn,
                                     const unsigned column)
    : Action(next_turn), column(column) {}

std::string ConnectFourAction::serialize() const {
    return "place token in column " + std::to_string(column);
}
