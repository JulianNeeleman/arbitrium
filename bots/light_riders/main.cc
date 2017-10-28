#include <iostream>
#include <sstream>
#include <string>

#include "games/tron/tron_action.h"
#include "games/tron/tron_state.h"
#include "players/minimax/minimax.h"

int main() {
    // Game information.
    unsigned id;
    TronState state;
    Minimax<TronState, TronAction> bot(6);

    std::string line, cmd;
    std::stringstream buffer;
    while (getline(std::cin, line)) {
        buffer.clear();
        buffer.str(line);

        getline(buffer, cmd, ' ');
        if (cmd == "action") {
            TronAction action = bot.choose_action(state);
            std::cout << action.serialize();
        } else if (cmd == "update") {
            getline(buffer, cmd, ' ');
            getline(buffer, cmd, ' ');
            if (cmd == "field") {
                std::vector<std::vector<char>> board(16, std::vector<char>(16));
                for (unsigned i = 0; i < 16; i++) {
                    for (unsigned j = 0; j < 16; j++) {
                        buffer >> board[i][j];
                    }
                }
                state = TronState(id, board);
            }
        } else {
            getline(buffer, cmd, ' ');
            if (cmd == "your_botid") {
                getline(buffer, cmd, ' ');
                id = std::stoi(cmd);
            }
        }
    }

    return 0;
}
