#ifndef AGENTS_HUMAN_HUMAN_H
#define AGENTS_HUMAN_HUMAN_H

#include "../../core/player.h"

#include <iostream>

template <class State, class Action>
class Human : public Player<State, Action> {
  public:
    // Constructors.
    Human();

    // Public member functions.
    Action choose_action(const State &) override;
};

#include "players/human/human.inc"

#endif // AGENTS_HUMAN_HUMAN_H
