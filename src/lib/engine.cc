#include "include/lib/engine.h"
#include <iostream>

Engine::Engine(std::unique_ptr<State> initial_state,
               std::vector<std::unique_ptr<Player>> players)
    : state_(std::move(initial_state)), players_(std::move(players)), turn_(1) {
    // Game loop.
    while (!state_->is_terminal()) {
        std::cout << turn_ << std::endl;
        next_turn();
    }
}

void Engine::next_turn() {
    // Request action from player.
    std::unique_ptr<Action> action = players_[turn_]->choose_action(state_);
    std::cout << "a" << std::endl;
    // Apply the action to the current engine state.
    state_ = state_->transition(action);

    // Increment turn counter.
    turn_ = -1 * turn_;
}
