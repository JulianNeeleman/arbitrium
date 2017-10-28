#ifndef TRON_STATE_H
#define TRON_STATE_H

#include "games/tron/tron_action.h"

#include <bitset>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

class TronState {
  private:
    // Private member variables.
    bool turn_;
    unsigned positions_[2];
    std::bitset<256> board_;

  public:
    // Constructors.
    TronState();
    TronState(bool, const std::vector<std::vector<char>> &);

    // Operator overloads.
    bool operator<(const TronState &) const;

    // Public member functions.
    TronState transition(const TronAction &) const;

    bool is_terminal() const;
    int result() const;
    double evaluate() const;
    std::vector<TronAction> actions() const;

    std::string serialize() const;

    // Getters.
    unsigned get_turn() const;
    void next_turn();
};

#endif // TRON_STATE_H
