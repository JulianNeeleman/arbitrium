#include "include/lib/engine.h"
#include "include/lib/player/human.h"
#include "include/lib/player/minimax.h"
#include "include/tic_tac_toe/tic_tac_toe_state.h"

int main() {
    TicTacToeState state;
    std::vector<std::unique_ptr<Player<TicTacToeState, TicTacToeAction>>>
        players;
    players.push_back(std::unique_ptr<Player<TicTacToeState, TicTacToeAction>>(
        new Minimax<TicTacToeState, TicTacToeAction>(15)));
    players.push_back(std::unique_ptr<Player<TicTacToeState, TicTacToeAction>>(
        new Minimax<TicTacToeState, TicTacToeAction>(15)));
    Engine<TicTacToeState, TicTacToeAction>(state, players);
    return 0;
}
