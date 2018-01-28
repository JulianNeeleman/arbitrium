// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <memory>
#include <vector>

#include "agent.hpp"

template <class S, class A> class Engine {
  private:
    S state;
    const std::vector<std::unique_ptr<Agent<S, A>>> &agents;
    const bool verbose;

    void next_turn();
    void dump_log() const;
    void dump_result() const;

  public:
    Engine(const S &initial_state,
           const std::vector<std::unique_ptr<Agent<S, A>>> &agents,
           const bool verbose);
    unsigned run();
};

template <class S, class A>
Engine<S, A>::Engine(const S &initial_state,
                     const std::vector<std::unique_ptr<Agent<S, A>>> &agents,
                     const bool verbose)
    : state(initial_state), agents(std::move(agents)), verbose(verbose) {}

template <class S, class A> void Engine<S, A>::next_turn() {
    A action = agents[state.get_turn()]->query(state, 5000);
    if (verbose) {
        std::cout << "player " << state.get_turn() << " chose action \""
                  << action.serialize() << "\"" << std::endl;
    }
    state = state.transition(action);
}

template <class S, class A> void Engine<S, A>::dump_log() const {
    if (!verbose) {
        return;
    }
    std::cout << "state:" << std::endl << state.serialize() << std::endl;
    std::vector<A> actions = state.legal_actions();
    std::cout << "actions:" << std::endl;
    for (unsigned option = 0; option < actions.size(); option++) {
        std::cout << option << " " << actions[option].serialize() << std::endl;
    }
}

template <class S, class A> void Engine<S, A>::dump_result() const {
    if (!verbose) {
        return;
    }
    if (state.winner() == -1) {
        std::cout << "game ended in a draw" << std::endl;
    } else {
        std::cout << "player " << state.winner() << " wins" << std::endl;
    }
}

template <class S, class A> unsigned Engine<S, A>::run() {
    while (state.winner() == -2) {
        dump_log();
        next_turn();
    }
    dump_result();
    return state.winner();
}
#endif // ENGINE_HPP
