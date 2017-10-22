#include "include/lib/engine.h"
#include "include/lib/human.h"
#include "include/lib/minimax.h"
#include "include/tic_tac_toe/tic_tac_toe_state.h"

int main() {
    std::unique_ptr<State> state(new TicTacToeState());
    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::unique_ptr<Player>(new Human()));
    players.push_back(std::unique_ptr<Player>(new Human()));

    Engine(std::move(state), std::move(players));

    return 0;
}
