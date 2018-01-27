// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CONNECT_FOUR_ACTION_HPP
#define CONNECT_FOUR_ACTION_HPP

#include <string>

#include "../core/action.hpp"

class ConnectFourAction : public Action<ConnectFourAction> {
    friend class ConnectFourState;

    bool next_turn;
    unsigned row, column;

  public:
    ConnectFourAction(const bool, const unsigned, const unsigned);

    std::string serialize() const override;
};

#endif // CONNECT_FOUR_ACTION_HPP
