#include "games/connect_four/connect_four_state.h"
#include <iostream>

/**
 * Default constructor.
 */
ConnectFourState::ConnectFourState()
    : players_(2), turn_(0), board_(0ULL), columns_(std::vector<unsigned>(7, 0) {}

/**
 * Update the board with the action on a copy of the state.
 */
ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;

    // Apply changes to the state.
    unsigned row = columns[action.get_column()];
    child.board_[turn_] |= 1ULL << (row * COLUMN + action.get_column());
    child.columns_[action.get_column()]++;

    // Move turn to next player.
    child.turn_ = (turn_ + 1) % 2;

    return child;
}

/**
 * Provide a way to sort states in cache.
 */
bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    return tie(turn_, board_) < tie(rhs.turn_, rhs.board_);
}

/**
 * Check if a player has got Connect Four, or the board is full.
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

    long y = newboard & (newboard >> HEIGHT);
    if ((y & (y >> 2 * HEIGHT)) != 0) // check diagonal \
      return true;
        y = newboard & (newboard >> H1);
    if ((y & (y >> 2 * H1)) != 0) // check horizontal -
        return true;
    y = newboard & (newboard >> H2); // check diagonal /
    if ((y & (y >> 2 * H2)) != 0)
        return true;
    y = newboard & (newboard >> 1); // check vertical |
    return (y & (y >> 2)) != 0;

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

    for (unsigned column = 0; column < 7; column++) {
        if (columns_[column] < 6) {
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
    for (int row = 5; row >= 0; row--) {
        for (unsigned column = 0; column < 7; column++) {
            unsigned i = row * COLUMN + column;
            if ((board_[0] >> i) & 1ULL) {
                out += "0\t";
            } else if ((board_[1] >> i) & 1ULL) {
                out += "1\t";
            } else {
                out += "-1\t";
            }
        }
        out += '\n';
    }

    return out;
}

/**
 * Retrieve who's turn it is in this state.
 */
unsigned ConnectFourState::get_turn() const {
    return turn_; }
