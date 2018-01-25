// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include <array>
#include <cstdio>
#include <memory>
#include <random>
#include <vector>

#include "../agents/negamax.hpp"
#include "../agents/random.hpp"
#include "../core/agent.hpp"
#include "../core/engine.hpp"
#include "../games/tic_tac_toe_action.hpp"
#include "../games/tic_tac_toe_state.hpp"

int main() {
    srand(time(nullptr));
    TicTacToeState initial_state;
    std::array<int, 3> total = {0, 0, 0};
    for (unsigned i = 0; i < 3; i++) {
        std::cout << i << std::endl;
        std::vector<std::unique_ptr<Agent<TicTacToeState, TicTacToeAction>>>
            agents;
        std::unique_ptr<Agent<TicTacToeState, TicTacToeAction>> a(
            new Negamax<TicTacToeState, TicTacToeAction>(22)),
            b(new Negamax<TicTacToeState, TicTacToeAction>(22));
        agents.push_back(std::move(a));
        agents.push_back(std::move(b));
        Engine<TicTacToeState, TicTacToeAction> engine(initial_state, agents,
                                                       false);
        total.at(engine.run())++;
    }
    for (unsigned i = 0; i < 3; i++) {
        std::cout << i << " " << total.at(i) << std::endl;
    }
    return 0;
}
