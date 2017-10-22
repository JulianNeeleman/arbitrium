#ifndef LIB_HUMAN_H
#define LIB_HUMAN_H

#include "include/lib/action.h"
#include "include/lib/player.h"
#include "include/lib/state.h"

#include <iostream>
#include <memory>

class Human : public Player {
  private:
    // Private member variables.

    // Private member functions.

  public:
    // Constructors.
    Human();

    // Public member functions.
    std::unique_ptr<Action>
    choose_action(const std::unique_ptr<State> &) const override;
};

#endif // LIB_HUMAN_H
