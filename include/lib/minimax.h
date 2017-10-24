#ifndef LIB_MINIMAX_H
#define LIB_MINIMAX_H

#include "include/lib/player.h"

#include <limits>

template <class State>
template <class Action>
class Minimax : public Player<State, Action> {
  private:
    // Private member variables.
    int max_depth_;

    // Private member functions.
    double minimax(const State &, int, bool) const;

  public:
    // Constructors.
    Minimax(int);

    // Public member functions.
    Action choose_action(const State &) const override;

    // Setters.
    void set_max_depth(int);
};

#include "src/lib/minimax.cc"

#endif // LIB_MINIMAX_H
