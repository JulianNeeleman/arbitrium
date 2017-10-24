#ifndef TIC_TAC_TOE_STATE_H
#define TIC_TAC_TOE_STATE_H

#include "include/tic_tac_toe/tic_tac_toe_action.h"

#include <cassert>
#include <vector>

class TicTacToeState {
  private:
    // Private member variables.
    unsigned players_, turn_;
    std::vector<std::vector<int>> board_;

    // Private member functions.

  public:
    // Constructors.
    TicTacToeState();

    // Public member functions.
    TicTacToeState transition(const TicTacToeAction &) const;

    bool is_terminal() const;
    int result() const;
    double evaluate() const;
    std::vector<TicTacToeAction> actions() const;

    std::string serialize() const;

    // Getters.
    unsigned get_turn() const;
};

#endif // TIC_TAC_TOE_STATE_H
