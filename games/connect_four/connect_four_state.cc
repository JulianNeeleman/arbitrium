#include "games/connect_four/connect_four_state.h"
#include <iostream>

/**
 * Default constructor.
 */
ConnectFourState::ConnectFourState()
    : players_(2), turn_(0), board_(6, std::vector<int>(7, -1)) {}

/**
 * Update the board with the action on a copy of the state.
 */
ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;

    // Compute placed token location.
    unsigned row = 0;
    while (child.board_[action.get_column()][row] != -1) {
        row++;
    }

    // Column can't be full.
    assert(row < 6);

    // Apply changes to the model.
    child.board_[action.get_column()][row] = turn_;

    // Move turn to next player.
    child.turn_ = (turn_ + 1) % players_;

    return child;
}

/**
 * Provide a way to sort states in cache.
 */
bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    return turn_ == rhs.turn_ ? board_ < rhs.board_ : turn_ < rhs.turn_;
}

/**
 * Check if a player has got Tic-Tac-Toe, or the board is full.
 */
bool ConnectFourState::is_terminal() const {
    return evaluate() != 0.0 || actions().empty();
}

/**
 * Decide a winner, or declare a draw, when the game ends.
 */
int ConnectFourState::result() const {
    assert(is_terminal());
    double score = evaluate();
    if (score == 0.0) {
        // Draw.
        return -1;
    }

    // Decisive result.
    return score == 1.0 ? turn_ : !turn_;
}

/**
 * Evaluate the position. If the current player wins, return +1. If
 * he loses, return -1. Otherwise, return 0.
 */
double ConnectFourState::evaluate() const {
    // Check rows and columns.
    for (unsigned i = 0; i < 3; i++) {
        if (board_[i][0] != -1 && board_[i][0] == board_[i][1] &&
            board_[i][1] == board_[i][2]) {
            return board_[i][0] ? 1.0 : -1.0;
        }

        if (board_[0][i] != -1 && board_[0][i] == board_[1][i] &&
            board_[1][i] == board_[2][i]) {
            return board_[0][i] ? 1.0 : -1.0;
        }
    }

    // Check diagonals.
    if (board_[1][1] != -1 &&
        ((board_[0][0] != -1 && board_[0][0] == board_[1][1] &&
          board_[1][1] == board_[2][2]) ||
         (board_[0][2] == board_[1][1] && board_[1][1] == board_[2][0]))) {
        return board_[1][1] ? 1.0 : -1.0;
    }

    // No winner.
    return 0.0;
}

/**
 * Return all empty fields on the board, which are precisely the set of legal
 * actions.
 */
std::vector<ConnectFourAction> ConnectFourState::actions() const {
    std::vector<ConnectFourAction> legal;

    // Loop over the top row to check which
    // columns aren't full;
    for (unsigned column = 0; column < 7; column++) {
        if (board_[5][column] == -1) {
            legal.push_back(ConnectFourAction(column));
        }
    }
    return legal;
}

/**
 * Provide a serialization of the state.
 */
std::string ConnectFourState::serialize() const {
    std::string out = "";

    // Serialize the board.
    for (unsigned row = 0; row < 6; row++) {
        for (unsigned column = 0; column < 7; column++) {
            out += std::to_string(board_[row][column]) + '\t';
        }
        out += '\n';
    }

    return out;
}

/**
 * Retrieve who's turn it is in this state.
 */
unsigned ConnectFourState::get_turn() const { return turn_; }
