#include "include/tic_tac_toe/tic_tac_toe_state.h"
#include <iostream>

std::unique_ptr<State>
TicTacToeState::transition(const std::unique_ptr<Action> &action) const {
    TicTacToeState child(*this);
    TicTacToeAction *ttt_action = static_cast<TicTacToeAction *>(action.get());

    std::cout << ttt_action->get_i() << " " << ttt_action->get_j() << " "
              << action->get_player() << std::endl;
    child.board_[ttt_action->get_i()][ttt_action->get_j()] =
        action->get_player();
    return std::unique_ptr<State>(new TicTacToeState(child));
}

/**
 * Check if a player has got Tic-Tac-Toe, or the board is full.
 */
bool TicTacToeState::is_terminal() const {
    return evaluate() != 0.0 || actions().empty();
}

/**
 * Evaluate the position. If player one wins, return +1. If player two wins,
 * return -1. Otherwise, return 0.
 */
double TicTacToeState::evaluate() const {
    // Check rows and columns.
    for (unsigned i = 0; i < 3; i++) {
        if (abs(board_[i][0] + board_[i][1] + board_[i][2]) == 3) {
            return board_[i][0];
        }

        if (abs(board_[0][i] + board_[1][i] + board_[2][i]) == 3) {
            return board_[0][i];
        }
    }

    // Check diagonals.
    if (abs(board_[0][0] + board_[1][1] + board_[2][2]) == 3 ||
        abs(board_[0][2] + board_[1][1] + board_[2][0]) == 3) {
        return board_[1][1];
    }

    // No winner.
    return 0.0;
}

/**
 * Return all empty fields on the board, which are precisely the set of legal
 * actions.
 */
std::vector<std::unique_ptr<Action>> TicTacToeState::actions() const {
    std::vector<std::unique_ptr<Action>> legal;

    // Loop over the board fields.
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (!board_[i][j]) {
                legal.push_back(std::unique_ptr<TicTacToeAction>(
                    new TicTacToeAction(player_, i, j)));
            }
        }
    }
    return legal;
}

std::string TicTacToeState::serialize() const {
    std::string out = "";
    out += "BOARD:\n";

    // Serialize the board.
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            out += std::to_string(board_[i][j]) + '\t';
        }
        out += '\n';
    }

    out += "TURN: " + std::to_string(player_) + '\n';
    return out;
}
