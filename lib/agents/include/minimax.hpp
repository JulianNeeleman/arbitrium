#ifndef MINIMAX_H
#define MINIMAX_H

#include "../../core/src/cache.hpp"
#include "../../core/src/player.hpp"

#include <limits>

template <class State, class Action>
class Minimax : public Player<State, Action>, public Cache<State> {
  private:
    // Private member variables.
    int max_depth_;

    // Private member functions.
    double minimax(const State &, int, double, double, bool);

  public:
    // Constructors.
    Minimax(int);

    // Public member functions.
    Action choose_action(const State &) override;

    // Setters.
    void set_max_depth(int);
};

#include "../src/minimax.hpp"

#endif // MINIMAX_H
