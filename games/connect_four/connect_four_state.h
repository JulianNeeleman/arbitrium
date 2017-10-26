#ifndef CONNECT_FOUR_STATE_H
#define CONNECT_FOUR_STATE_H

#include "games/connect_four/connect_four_action.h"

#include <cassert>
#include <vector>

class ConnectFourState {
  private:
    // Private member variables.
    unsigned players_, turn_;
    std::vector<std::vector<int>> board_;

  public:
    // Constructors.
    ConnectFourState();

    // Operator overloads.
    bool operator<(const ConnectFourState &) const;

    // Public member functions.
    ConnectFourState transition(const ConnectFourAction &) const;

    bool is_terminal() const;
    int result() const;
    double evaluate() const;
    std::vector<ConnectFourAction> actions() const;

    std::string serialize() const;

    // Getters.
    unsigned get_turn() const;
};

#endif // CONNECT_FOUR_STATE_H
