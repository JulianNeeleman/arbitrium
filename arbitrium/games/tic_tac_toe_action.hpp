// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef TIC_TAC_TOE_ACTION_HPP
#define TIC_TAC_TOE_ACTION_HPP

#include <string>

#include "../core/action.hpp"

class TicTacToeAction : public Action<TicTacToeAction> {
    friend class TicTacToeState;

    unsigned i, j;

  public:
    TicTacToeAction(const unsigned, const unsigned, const unsigned);

    std::string serialize() const override;
};

#endif // TIC_TAC_TOE_ACTION_HPP
