#ifndef LIB_ENGINE_H
#define LIB_ENGINE_H

#include "lib/include/player.h"

#include <memory>
#include <string>
#include <vector>

template <class State, class Action> class Engine {
  private:
    // Private member variables.
    State state_;
    const std::vector<std::unique_ptr<Player<State, Action>>> &players_;
    int turn_;

    // Private member functions.
    void next_turn();
    void log() const;

  public:
    // Constructors.
    Engine(const State &,
           const std::vector<std::unique_ptr<Player<State, Action>>> &);
};

#include "lib/src/engine.inc"

#endif // LIB_ENGINE_H
