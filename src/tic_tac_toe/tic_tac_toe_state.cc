#include "include/tic_tac_toe/tic_tac_toe_state.h"
#include <iostream>

/**
 * Default constructor.
 */
TicTacToeState::TicTacToeState()
    : turn_(0), board_(3, std::vector<int>(3, -1)) {}

TicTacToeState TicTacToeState::transition(const TicTacToeAction &action) const {
    TicTacToeState child = *this;

    child.board_[action.get_i()][action.get_j()] = turn_;
    return child;
}

/**
 * Check if a player has got Tic-Tac-Toe, or the board is full.
 */
bool TicTacToeState::is_terminal() const {
    return evaluate() != 0.0 || actions().empty();
}

int TicTacToeState::result() const {
    assert(is_terminal());
    double eval = evaluate();
    if (eval == 0.0) {
        // Draw.
        return -1;
    }

    // Decisive result.
    return eval == 1.0 ? turn_ : !turn_;
}

/**
 * Evaluate the position. If the current player wins, return +1. If
 * he loses, return -1. Otherwise, return 0.
 */
double TicTacToeState::evaluate() const {
    // Check rows and columns.
    for (unsigned i = 0; i < 3; i++) {
        if (board_[i][0] != -1 && board_[i][0] == board_[i][1] &&
            board_[i][1] == board_[i][2]) {
            return board_[i][0] == static_cast<int>(turn_) ? 1.0 : -1.0;
        }

        if (board_[0][i] != -1 && board_[0][i] == board_[1][i] &&
            board_[1][i] == board_[2][i]) {
            return board_[0][i] == static_cast<int>(turn_) ? 1.0 : -1.0;
        }
    }

    // Check diagonals.
    if (board_[1][1] != -1 &&
        ((board_[0][0] != -1 && board_[0][0] == board_[1][1] &&
          board_[1][1] == board_[2][2]) ||
         (board_[0][2] == board_[1][1] && board_[1][1] == board_[2][0]))) {
        return board_[1][1] == static_cast<int>(turn_) ? 1.0 : -1.0;
    }

    // No winner.
    return 0.0;
}

/**
 * Return all empty fields on the board, which are precisely the set of legal
 * actions.
 */
std::vector<TicTacToeAction> TicTacToeState::actions() const {
    std::vector<TicTacToeAction> legal;

    // Loop over the board fields.
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (board_[i][j] == -1) {
                legal.push_back(TicTacToeAction(i, j));
            }
        }
    }
    return legal;
}

std::string TicTacToeState::serialize() const {
    std::string out = "";

    // Serialize the board.
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            out += std::to_string(board_[i][j]) + '\t';
        }
        out += '\n';
    }

    return out;
}

unsigned TicTacToeState::get_turn() const { return turn_; }

void TicTacToeState::set_turn(unsigned turn) { turn_ = turn; }
