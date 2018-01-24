// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include <cstdio>
#include <memory>
#include <random>
#include <vector>

int main() {
    srand(time(NULL));
    TicTacToeState initial_state;
    std::vector<std::unique_ptr<Agent<TicTacToeState, TicTacToeAction>>> agents;
    std::unique_ptr<Agent<TicTacToeState, TicTacToeAction>> a(
        new Random<TicTacToeState, TicTacToeAction>),
        b(new Random<TicTacToeState, TicTacToeAction>);
    agents.push_back(std::move(a));
    agents.push_back(std::move(b));
    Engine<TicTacToeState, TicTacToeAction> engine(initial_state, agents);
    engine.run();
    return 0;
}
