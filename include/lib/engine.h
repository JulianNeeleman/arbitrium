#ifndef LIB_ENGINE_H
#define LIB_ENGINE_H

#include "include/lib/player.h"
#include "include/lib/state.h"

#include <string>

class Engine {
  protected:
    // Private member variables.
    std::unique_ptr<State> state_;
    std::vector<std::unique_ptr<Player>> players_;
    int turn_;

    // Private member functions.
    void next_turn();

  public:
    // Constructors.
    Engine(std::unique_ptr<State>, std::vector<std::unique_ptr<Player>>);

    // Public member functions.
};

#endif // LIB_ENGINE_H
