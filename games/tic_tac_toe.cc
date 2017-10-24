#include "include/lib/engine.h"
#include "include/lib/human.h"
#include "include/tic_tac_toe/tic_tac_toe_state.h"

int main() {
    TicTacToeState state;
    std::vector<std::unique_ptr<Player<TicTacToeState, TicTacToeAction>>>
        players;
    players.push_back(std::unique_ptr<Player<TicTacToeState, TicTacToeAction>>(
        new Human<TicTacToeState, TicTacToeAction>()));
    players.push_back(std::unique_ptr<Player<TicTacToeState, TicTacToeAction>>(
        new Human<TicTacToeState, TicTacToeAction>()));
    Engine<TicTacToeState, TicTacToeAction>(state, players);
    return 0;
}
