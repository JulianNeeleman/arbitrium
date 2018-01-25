// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "connect_four_state.hpp"

ConnectFourState::ConnectFourState()
    : State(), board({{0, 0}}), heights({{0, 0, 0, 0, 0, 0, 0}}) {}

bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    unsigned l_turn = current_agent(), r_turn = rhs.current_agent();
    return l_turn == r_turn ? board < rhs.board : l_turn < r_turn;
}

std::vector<ConnectFourAction> ConnectFourState::legal_actions() const {
    std::vector<ConnectFourAction> actions;
    for (unsigned column = 0; column < 7; column++) {
        if (heights.at(column) < 6) {
            actions.push_back({other_agent(), column});
        }
    }
    return actions;
}

ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;
    int64_t bit = 1ULL << child.heights.at(action.column)++;
    child.board.at(current_agent() - 1) ^= bit;
    child.turn = action.next_agent == 2;
    return child;
}

int ConnectFourState::winner() const {
    std::array<unsigned, 4> directions{1, 6, 7, 8};
    int64_t side = board.at(other_agent() - 1), acc;
    for (unsigned direction : directions) {
        acc = side & (side >> direction);
        if ((acc & (acc >> (2 * direction))) != 0) {
            return other_agent();
        }
    }
    return legal_actions().empty() ? 0 : -1;
}

double ConnectFourState::evaluate() const { return 0; }

std::string ConnectFourState::serialize() const {
    std::string serialization = "";
    for (int i = 5; i >= 0; i--) {
        for (unsigned j = 0; j < 7; j++) {
            if (static_cast<bool>(board.at(0) >> (i + j * 7))) {
                serialization += "1\t";
            }
            else if (static_cast<bool>(board.at(1) >> (i + j * 7))) {
                serialization += "2\t";
            } else {
                serialization += ".\t";
            }
        }
        serialization += '\n';
    }
    return serialization;
}
