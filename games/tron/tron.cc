#include "games/tron/tron_state.h"
#include "lib/include/engine.h"
#include "players/human/human.h"
#include "players/minimax/minimax.h"

int main() {
    TronState state;
    std::vector<std::unique_ptr<Player<TronState, TronAction>>> players;
    players.push_back(std::unique_ptr<Player<TronState, TronAction>>(
        new Minimax<TronState, TronAction>(6)));
    players.push_back(std::unique_ptr<Player<TronState, TronAction>>(
        new Minimax<TronState, TronAction>(9)));
    Engine<TronState, TronAction>(state, players);
    return 0;
}
