#ifndef LIB_HUMAN_H
#define LIB_HUMAN_H

#include "include/lib/player.h"

#include <iostream>
#include <memory>

template <class State, class Action>
class Human : public Player<State, Action> {
  public:
    // Constructors.
    Human();

    // Public member functions.
    Action choose_action(const State &) const override;
};

#include "src/lib/player/human.inc"

#endif // LIB_HUMAN_H
