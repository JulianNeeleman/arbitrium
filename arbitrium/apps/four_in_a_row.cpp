// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include <string>
#include <vector>

#include "../agents/negamax.hpp"
#include "../competitions/connect_four_bot.hpp"

#include "../games/connect_four_state.cpp"
#include "../games/connect_four_action.cpp"

int main() {
    ConnectFourBot<Negamax<ConnectFourState, ConnectFourAction>> bot;
    bot.run();
    return 0;
}