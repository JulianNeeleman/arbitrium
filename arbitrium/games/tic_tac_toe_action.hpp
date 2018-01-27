// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef TIC_TAC_TOE_ACTION_HPP
#define TIC_TAC_TOE_ACTION_HPP

#include <string>

#include "../core/action.hpp"

class TicTacToeAction : public Action<TicTacToeAction> {
    friend class TicTacToeState;

    bool next_turn;
    unsigned row, column;

  public:
    TicTacToeAction(const bool next_turn, const unsigned row, const unsigned column);

    std::string serialize() const override;
};

#endif // TIC_TAC_TOE_ACTION_HPP
