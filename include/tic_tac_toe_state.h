#ifndef TIC_TAC_TOE_STATE_H
#define TIC_TAC_TOE_STATE_H

#include "include/lib/state.h"
#include "include/tic_tac_toe_action.h"

#include <memory>
#include <vector>

class TicTacToeState : public State {
  private:
    // Private member variables.
    int board_[3][3];

    // Private member functions.

  public:
    // Constructors.
    TicTacToeState() = default;

    // Public member functions.
    std::unique_ptr<State>
    transition(const std::unique_ptr<Action> &) const override;

    bool is_terminal() const override;
    double evaluate() const override;
    std::vector<std::unique_ptr<Action>> actions() const override;

    std::string serialize() const override;
    // Setters.
};

#endif // TIC_TAC_TOE_STATE_H
