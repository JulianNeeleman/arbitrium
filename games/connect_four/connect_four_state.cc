#include "games/connect_four/connect_four_state.h"
#include <iostream>

/**
 * Default constructor.
 */
ConnectFourState::ConnectFourState()
    : players_(2), turn_(0), board_{0ULL, 0ULL},
      columns_(std::vector<unsigned>(7, 0)) {}

/**
 * Update the board with the action on a copy of the state.
 */
ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;

    // Apply changes to the state.
    unsigned row = columns_[action.get_column()];
    child.board_[turn_] |= 1ULL << (row + action.get_column() * (ROWS + 1));
    child.columns_[action.get_column()]++;

    // Move turn to next player.
    child.turn_ = (turn_ + 1) % players_;

    return child;
}

/**
 * Provide a way to sort states in cache.
 */
bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    return std::tie(turn_, board_) < std::tie(rhs.turn_, rhs.board_);
}

/**
 * Check if a player has got Connect Four, or the board is full.
 */
bool ConnectFourState::is_terminal() const {
    return evaluate_player(0) || evaluate_player(1) || actions().empty();
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
 *  Evaluate a single bitboard, representing one of
 *  the players' tokens.
 */
double ConnectFourState::evaluate_player(bool player) const {
    // Declare the player's tokens and the union of both players tokens.
    int64_t p = board_[player], q = p & (p >> ROWS);

    // Check contra-diagonal.
    if (q & (q >> 2 * ROWS)) {
        return 1.0;
    }

    // Check horizontal.
    q = p & (p >> (ROWS + 1));
    if (q & (q >> 2 * (ROWS + 1))) {
        return 1.0;
    }

    // Check diagonal.
    q = p & (p >> (ROWS + 2));
    if (q & (q >> 2 * (ROWS + 2))) {
        return 1.0;
    }

    // Check vertical.
    q = p & (p >> 1);
    return (q & (q >> 2)) ? 1.0 : 0.0;
}

/**
 * Evaluate the position. If the player one wins, return +1. If
 * he loses, return -1. Otherwise, return 0.
 */
double ConnectFourState::evaluate() const {
    return evaluate_player(1) - evaluate_player(0);
}

/**
 * Return all empty fields on the board, which are precisely the set of
 * legal
 * actions.
 */
std::vector<ConnectFourAction> ConnectFourState::actions() const {
    std::vector<ConnectFourAction> legal;

    for (unsigned column : {3, 2, 4, 1, 5, 0, 6}) {
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
            unsigned i = row + column * (ROWS + 1);
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
unsigned ConnectFourState::get_turn() const { return turn_; }
