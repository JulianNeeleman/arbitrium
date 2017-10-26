#ifndef LIB_HUMAN_H
#define LIB_HUMAN_H

#include "lib/include/player.h"

#include <iostream>

template <class State, class Action>
class Human : public Player<State, Action> {
  public:
    // Constructors.
    Human();

    // Public member functions.
    Action choose_action(const State &) const override;
};

#include "players/human/human.inc"

#endif // LIB_HUMAN_H
