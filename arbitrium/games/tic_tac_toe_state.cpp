// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "tic_tac_toe_state.hpp"

TicTacToeState::TicTacToeState()
    : State(), board({{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}) {}

bool TicTacToeState::operator<(const TicTacToeState &rhs) const {
    unsigned l_turn = current_agent(), r_turn = rhs.current_agent();
    return l_turn == r_turn ? board < rhs.board : l_turn < r_turn;
}

std::vector<TicTacToeAction> TicTacToeState::legal_actions() const {
    std::vector<TicTacToeAction> actions;
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (board.at(i).at(j) == 0) {
                actions.push_back(TicTacToeAction(other_agent(), i, j));
            }
        }
    }
    return actions;
}

TicTacToeState TicTacToeState::transition(const TicTacToeAction &action) const {
    TicTacToeState child = *this;
    child.board.at(action.i).at(action.j) = current_agent();
    child.turn = action.next_agent == 2;
    return child;
}

int TicTacToeState::winner() const {
    double score = evaluate();
    if (score != 0) {
        return other_agent();
    }
    return legal_actions().empty() ? 0 : -1;
}

bool TicTacToeState::check(const std::array<unsigned, 3> &cells) const {
    for (unsigned cell : cells) {
        if (cell == 0 || cell == current_agent()) {
            return false;
        }
    }
    return true;
}

double TicTacToeState::evaluate() const {
    for (unsigned i = 0; i < 3; i++) {
        if (check(board.at(i)) ||
            check({board.at(0).at(i), board.at(1).at(i), board.at(2).at(i)})) {
            return -1;
        }
    }

    if (check({board.at(0).at(0), board.at(1).at(1), board.at(2).at(2)}) ||
        check({board.at(0).at(2), board.at(1).at(1), board.at(2).at(0)})) {
        return -1;
    }
    return 0;
}

std::string TicTacToeState::serialize() const {
    std::string serialization = "";
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            serialization += std::to_string(board.at(i).at(j)) + '\t';
        }
        serialization += '\n';
    }
    return serialization;
}
