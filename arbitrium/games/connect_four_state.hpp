// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CONNECT_FOUR_STATE_HPP
#define CONNECT_FOUR_STATE_HPP

#include <array>

#include "../core/state.hpp"
#include "connect_four_action.hpp"

class ConnectFourState : public State<ConnectFourState, ConnectFourAction> {
    std::array<int64_t, 2> board;
    std::array<int, 7> heights;

  public:
    ConnectFourState();
    ConnectFourState(const bool, const std::array<int64_t, 2>);

    bool operator<(const ConnectFourState &rhs) const override;

    std::vector<ConnectFourAction> legal_actions() const override;
    ConnectFourState transition(const ConnectFourAction &action) const override;

    int winner() const override;
    bool check(const std::array<unsigned, 4> &) const;
    double evaluate() const override;

    std::string serialize() const override;
};

#endif // CONNECT_FOUR_STATE_HPP
