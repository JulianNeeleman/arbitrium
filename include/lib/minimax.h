#ifndef LIB_MINIMAX_H
#define LIB_MINIMAX_H

#include "include/lib/action.h"
#include "include/lib/state.h"

#include <limits>
#include <memory>

class Minimax {
  private:
    // Private member variables.
    int max_depth_;

    // Private member functions.
    double minimax(const std::unique_ptr<State> &, int, bool) const;

  public:
    // Constructors.
    Minimax(int);

    // Public member functions.
    std::unique_ptr<Action> choose_action(const std::unique_ptr<State> &) const;

    // Setters.
    void set_max_depth(int);
};

#endif // LIB_MINIMAX_H
