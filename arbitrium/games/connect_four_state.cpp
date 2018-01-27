// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "connect_four_state.hpp"

ConnectFourState::ConnectFourState() : BitboardPair<6, 7>(), heights{} {}

ConnectFourState::ConnectFourState(
    const std::pair<Bitboard<6, 7>, Bitboard<6, 7>> &board, const bool turn)
    : BitboardPair<6, 7>(board, turn), heights{} {}

bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    return BitboardPair<6, 7>::operator<(rhs);
}

std::vector<ConnectFourAction> ConnectFourState::legal_actions() const {
    std::vector<ConnectFourAction> actions;
    for (unsigned column = 0; column < 7; column++) {
        if (heights.at(column) < 6) {
            actions.push_back({!turn, heights.at(column), column});
        }
    }
    return actions;
}

ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;
    child.current_agent_board().set(action.row, action.column, true);
    child.heights.at(action.column) = action.row + 1;
    child.turn = action.next_turn;
    return child;
}

int ConnectFourState::winner() const {
    if (current_agent_board().four_consecutive_bits()) {
        return static_cast<int>(turn);
    }
    if (other_agent_board().four_consecutive_bits()) {
        return static_cast<int>(!turn);
    }
    return legal_actions().empty() ? -1 : -2;
}

std::string ConnectFourState::serialize() const {
    return BitboardPair<6, 7>::serialize();
}

unsigned ConnectFourState::get_turn() const {
    return static_cast<unsigned>(turn);
}
