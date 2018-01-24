// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "engine.hpp"

atemplate <class S, class A>
Engine<S, A>::Engine(const S &state,
                     const std::vector<std::unique_ptr<Agent<S, A>>> &agents)
    : state(state), agents(std::move(agents)) {}

template <class S, class A> void Engine<S, A>::next_turn() {
    A action = agents[state.current_agent() - 1]->query(state);
    std::cout << "player " << state.current_agent() << " chose action \""
              << action.serialize() << std::endl;
    state = state.transition(action);
}

template <class S, class A> void Engine<S, A>::dump_log() const {
    std::cout << "state:" << std::endl << state.serialize() << std::endl;
    std::vector<A> actions = state.legal_actions();
    std::cout << "actions:" << std::endl;
    for (unsigned option = 0; option < actions.size(); option++) {
        std::cout << option << " " << actions[option].serialize() << std::endl;
    }
}

template <class S, class A> void Engine<S, A>::run() {
    while (state.winner() == -1) {
        dump_log();
        next_turn();
    }
}
