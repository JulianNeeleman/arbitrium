// Copyright 2018 ReSnap b.v. All Rights Reserved.

TicTacToeState::TicTacToeState()
    : State(), board({{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}) {}

bool TicTacToeState::operator<(const TicTacToeState &rhs) const {
    bool l_turn = current_agent(), r_turn = rhs.current_agent();
    return l_turn == r_turn ? board < rhs.board : l_turn < r_turn;
}

std::vector<TicTacToeAction> TicTacToeState::legal_actions() const {
    std::vector<TicTacToeAction> actions;
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                actions.push_back(TicTacToeAction(other_agent(), i, j));
            }
        }
    }
    return actions;
}

TicTacToeState TicTacToeState::transition(const TicTacToeAction &action) const {
    TicTacToeState child = *this;
    child.board[action.i][action.j] = current_agent();
    child.turn = action.next_agent - 1;
    return child;
}

int TicTacToeState::winner() const {
    double score = evaluate();
    if (score != 0) {
        return other_agent();
    }
    return legal_actions().empty() ? 0 : -1;
}

bool TicTacToeState::check_cells(const std::array<unsigned, 3> &cells) const {
    for (unsigned cell : cells) {
        if (cell == 0 || cell == current_agent()) {
            return false;
        }
    }
    return true;
}

double TicTacToeState::evaluate() const {
    for (unsigned i = 0; i < 3; i++) {
        if (check_cells(board[i]) ||
            check_cells({board[0][i], board[1][i], board[2][i]})) {
            return -1;
        }
    }

    if (check_cells({board[0][0], board[1][1], board[2][2]}) ||
        check_cells({board[0][2], board[1][1], board[2][0]})) {
        return -1;
    }
    return 0;
}

std::string TicTacToeState::serialize() const {
    std::string serialization = "";
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            serialization += std::to_string(board[i][j]) + '\t';
        }
        serialization += '\n';
    }
    return serialization;
}
