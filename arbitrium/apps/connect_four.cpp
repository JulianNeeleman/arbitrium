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
#include "../games/connect_four_action.hpp"
#include "../games/connect_four_state.hpp"

int main() {
    srand(time(nullptr));
    ConnectFourState initial_state;
    std::array<int, 3> total = {0, 0, 0};
    for (unsigned i = 0; i < 1; i++) {
        std::vector<std::unique_ptr<Agent<ConnectFourState, ConnectFourAction>>>
            agents;
        std::unique_ptr<Agent<ConnectFourState, ConnectFourAction>> a(
            new Negamax<ConnectFourState, ConnectFourAction>),
            b(new Negamax<ConnectFourState, ConnectFourAction>);
        agents.push_back(std::move(a));
        agents.push_back(std::move(b));
        Engine<ConnectFourState, ConnectFourAction> engine(initial_state,
                                                           agents, true);
        int result = engine.run();
        total.at(result < 0 ? 2 : result)++;
    }
    for (unsigned i = 0; i < 3; i++) {
        std::cout << i << " " << total.at(i) << std::endl;
    }
    return 0;
}
