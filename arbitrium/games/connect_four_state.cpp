// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include <iostream>

#include "connect_four_state.hpp"

ConnectFourState::ConnectFourState()
    : State(false), board({{0, 0}}), heights({{0, 0, 0, 0, 0, 0, 0}}) {}

ConnectFourState::ConnectFourState(const bool turn,
                                   const std::array<int64_t, 2> board,
                                   const std::array<int, 7> heights)
    : State(turn), board(board), heights(heights) {}

bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    unsigned l_turn = current_agent(), r_turn = rhs.current_agent();
    return l_turn == r_turn ? board < rhs.board : l_turn < r_turn;
}

std::vector<ConnectFourAction> ConnectFourState::legal_actions() const {
    std::vector<ConnectFourAction> actions;
    for (unsigned column = 0; column < 7; column++) {
        // std::cout << heights.at(column) << " ";
        if (heights.at(column) < 6) {
            actions.push_back({other_agent(), column});
        }
    }
    // std::cout << std::endl;
    return actions;
}

ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;
    int64_t bit = 1LL << (child.heights.at(action.column) + 7 * action.column);
    child.board.at(current_agent() - 1) |= bit;
    child.heights.at(action.column)++;
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

double ConnectFourState::evaluate() const {
    return winner() == other_agent() ? -1 : 0;
}

std::string ConnectFourState::serialize() const {
    std::string serialization = "";
    for (int i = 5; i >= 0; i--) {
        for (unsigned j = 0; j < 7; j++) {
            if ((board.at(0) >> (i + j * 7)) % 2 == 1) {
                serialization += "1\t";
            } else if ((board.at(1) >> (i + j * 7)) % 2 == 1) {
                serialization += "2\t";
            } else {
                serialization += ".\t";
            }
        }
        serialization += '\n';
    }
    return serialization;
}
