// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "tic_tac_toe_state.hpp"

TicTacToeState::TicTacToeState() : BitboardPair<3, 3>() {}

TicTacToeState::TicTacToeState(
    const std::pair<Bitboard<3, 3>, Bitboard<3, 3>> &board, const bool turn)
    : BitboardPair<3, 3>(board, turn) {}

bool TicTacToeState::operator<(const TicTacToeState &rhs) const {
    return BitboardPair<3, 3>::operator<(rhs);
}

std::vector<TicTacToeAction> TicTacToeState::legal_actions() const {
    std::vector<TicTacToeAction> actions;
    for (unsigned row = 0; row < 3; row++) {
        for (unsigned column = 0; column < 3; column++) {
            if (!board_union().get(row, column)) {
                actions.push_back({!turn, row, column});
            }
        }
    }
    return actions;
}

TicTacToeState TicTacToeState::transition(const TicTacToeAction &action) const {
    TicTacToeState child = *this;
    child.current_agent_board().set(action.row, action.column, true);
    child.turn = action.next_turn;
    return child;
}

int TicTacToeState::winner() const {
    if (current_agent_board().three_consecutive_bits()) {
        return static_cast<int>(turn);
    }
    if (other_agent_board().three_consecutive_bits()) {
        return static_cast<int>(!turn);
    }
    return legal_actions().empty() ? -1 : -2;
}

std::string TicTacToeState::serialize() const {
    return BitboardPair<3, 3>::serialize();
}

unsigned TicTacToeState::get_turn() const {
    return static_cast<unsigned>(turn);
}
