// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CONNECT_FOUR_STATE_HPP
#define CONNECT_FOUR_STATE_HPP

#include <array>
#include <tuple>

#include "../core/bitboard_pair.hpp"
#include "../core/state.hpp"
#include "connect_four_action.hpp"

class ConnectFourState : public State<ConnectFourState, ConnectFourAction>,
                         public BitboardPair<6, 7> {
    std::array<unsigned, 7> heights;

  public:
    ConnectFourState();
    explicit ConnectFourState(
        const std::pair<Bitboard<6, 7>, Bitboard<6, 7>> &board,
        const bool turn);

    bool operator<(const ConnectFourState &rhs) const override;

    std::vector<ConnectFourAction> legal_actions() const override;
    ConnectFourState transition(const ConnectFourAction &action) const override;

    int winner() const override;
    bool check(const std::array<unsigned, 4> &) const;
    double evaluate() const override;

    std::string serialize() const override;

    unsigned get_turn() const override;
};

#endif // CONNECT_FOUR_STATE_HPP
