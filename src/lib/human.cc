#include "include/lib/human.h"

/**
 * Assignment constructor.
 */
Human::Human() {}

/**
 * Choose the best action from the current state.
 */
std::unique_ptr<Action>
Human::choose_action(const std::unique_ptr<State> &state) const {
    std::cout << state->serialize();
    std::vector<std::unique_ptr<Action>> actions = state->actions();
    for (unsigned option = 0; option < actions.size(); option++) {
        std::cout << option << ". " << actions[option]->serialize();
    }

    unsigned choice;
    std::cin >> choice;

    return std::move(actions[choice]);
}
