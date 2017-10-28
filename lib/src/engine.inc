#include "lib/include/engine.h"

template <class State, class Action>
Engine<State, Action>::Engine(
    const State &initial_state,
    const std::vector<std::unique_ptr<Player<State, Action>>> &players)
    : state_(initial_state), players_(std::move(players)) {
    // Game loop.
    while (!state_.is_terminal()) {
        log();
        next_simultaneous_turn();
    }
}

template <class State, class Action> void Engine<State, Action>::next_turn() {
    // Request action from player.
    Action action = players_[state_.get_turn()]->choose_action(state_);
    std::cout << "PLAYER " << state_.get_turn() << " CHOSE ACTION "
              << action.serialize();

    // Apply the action to the current engine state.
    state_ = state_.transition(action);
}

template <class State, class Action>
void Engine<State, Action>::next_simultaneous_turn() {
    std::vector<Action> actions;

    // Request action from both players.
    for (unsigned player = 0; player < players_.size(); player++) {
        actions.push_back(players_[state_.get_turn()]->choose_action(state_));
        state_.next_turn();
        std::cout << "PLAYER " << state_.get_turn() << " CHOSE ACTION "
                  << actions[player].serialize();
    }

    // Apply the actions to the current engine state.
    for (unsigned player = 0; player < players_.size(); player++) {
        state_ = state_.transition(actions[player]);
    }
}

template <class State, class Action> void Engine<State, Action>::log() const {
    std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "STATE:\n" << state_.serialize();
    std::vector<Action> actions = state_.actions();
    std::cout << "ACTIONS:\n";
    for (unsigned option = 0; option < actions.size(); option++) {
        std::cout << option << ". " << actions[option].serialize();
    }
}
