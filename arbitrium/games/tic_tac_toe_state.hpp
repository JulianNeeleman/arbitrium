// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef TIC_TAC_TOE_STATE_HPP
#define TIC_TAC_TOE_STATE_HPP

#include <array>

#include "../core/state.hpp"
#include "tic_tac_toe_action.hpp"

class TicTacToeState : public State<TicTacToeState, TicTacToeAction> {
    std::array<std::array<unsigned, 3>, 3> board;

  public:
    TicTacToeState();

    bool operator<(const TicTacToeState &rhs) const override;

    std::vector<TicTacToeAction> legal_actions() const override;
    TicTacToeState transition(const TicTacToeAction &action) const override;

    int winner() const override;
    bool check(const std::array<unsigned, 3> &) const;
    double evaluate() const override;

    std::string serialize() const override;
};

#endif // TIC_TAC_TOE_STATE_HPP
