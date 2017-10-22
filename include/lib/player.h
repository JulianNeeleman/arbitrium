#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include "include/lib/action.h"
#include "include/lib/state.h"

#include <memory>

class Player {
  private:
    // Private member variables.

    // Private member functions.

  public:
    // Public member functions.
    virtual std::unique_ptr<Action>
    choose_action(const std::unique_ptr<State> &) const = 0;

    // Setters.
};

#endif // LIB_PLAYER_H
