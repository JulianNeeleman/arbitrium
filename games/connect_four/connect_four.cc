#include "games/connect_four/connect_four_state.h"
#include "lib/include/engine.h"
#include "players/human/human.h"
#include "players/minimax/minimax.h"

int main() {
    ConnectFourState state;
    std::vector<std::unique_ptr<Player<ConnectFourState, ConnectFourAction>>>
        players;
    players.push_back(
        std::unique_ptr<Player<ConnectFourState, ConnectFourAction>>(
            new Minimax<ConnectFourState, ConnectFourAction>(8)));
    players.push_back(
        std::unique_ptr<Player<ConnectFourState, ConnectFourAction>>(
            new Human<ConnectFourState, ConnectFourAction>()));
    Engine<ConnectFourState, ConnectFourAction>(state, players);
    return 0;
}
